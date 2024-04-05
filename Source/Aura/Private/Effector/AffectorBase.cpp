// Copyright, Wisle25

#include "Effector/AffectorBase.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"

AAffectorBase::AAffectorBase()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root Scene");
	RootComponent->SetMobility(EComponentMobility::Static);

	// Interaction Box
	InteractBox = CreateDefaultSubobject<UBoxComponent>("Collision Box");
	InteractBox->SetMobility(EComponentMobility::Static);
	InteractBox->SetupAttachment(RootComponent);
	InteractBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	InteractBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	InteractBox->SetGenerateOverlapEvents(true);

	// Mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetMobility(EComponentMobility::Static);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Particle
	Particle = CreateDefaultSubobject<UNiagaraComponent>("Particle");
	Particle->SetupAttachment(RootComponent);
	Particle->SetMobility(EComponentMobility::Static);
	Particle->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

///////////////////////////////////////////////////////////
// ==================== Lifecycles ==================== //

void AAffectorBase::BeginPlay()
{
	Super::BeginPlay();

	DetermineComponents();
	InitInteraction();
}

//////////////////////////////////////////////////////////
// ==================== Components ==================== //

void AAffectorBase::DetermineComponents()
{
	// Visual Type
	switch (VisualType)
	{
	case EVisualType::EVT_Mesh:
		if (Particle) Particle->DestroyComponent();
		break;

	case EVisualType::EVT_Particle:
		if (Mesh) Mesh->DestroyComponent();
		break;
	}
}

///////////////////////////////////////////////////////////
// ==================== Interaction ==================== //

void AAffectorBase::InitInteraction()
{
	if (IsValid(InteractBox))
	{
		InteractBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnEnterInteraction);
		InteractBox->OnComponentEndOverlap  .AddDynamic(this, &ThisClass::OnLeaveInteraction);
	}
}

void AAffectorBase::OnEnterInteraction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Applying
	if (ApplyWhen == EApplyWhen::EAW_BeginOverlap)
		ApplyEffectTo(OtherActor);
}

void AAffectorBase::OnLeaveInteraction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Applying
	if (ApplyWhen == EApplyWhen::EAW_EndOverlap)
		ApplyEffectTo(OtherActor);

	// Removing
	if (RemoveWhen == ERemoveWhen::ERW_EndOverlap)
		RemoveEffectFrom(OtherActor);		
}

void AAffectorBase::ApplyEffectTo(AActor* Target)
{
	if (IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(Target))
	{
		// NOTE: AS is Ability System
		UAbilitySystemComponent* TargetAS = ASI->GetAbilitySystemComponent();

		// Destroy if needed
		if (bInstantDestroy)
			Destroy();

		// Spec
		FGameplayEffectContextHandle CtxHandle = TargetAS->MakeEffectContext();
		CtxHandle.AddSourceObject(this);

		// Finally apply multiple effects
		for (const auto& GameplayEffect : GameplayEffectClasses)
		{
			const FGameplayEffectSpecHandle EffectSpec = TargetAS->MakeOutgoingSpec(GameplayEffect, Level, CtxHandle);
			const FActiveGameplayEffectHandle Handler  = TargetAS->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data.Get());

			// Add to removing query
			if (RemoveWhen == ERemoveWhen::ERW_EndOverlap)
				ActiveEffectHandlers.Add(TargetAS, Handler);
		}
	}
}

void AAffectorBase::RemoveEffectFrom(AActor* Target)
{
	if (IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(Target))
	{
		// NOTE: AS is Ability System
		UAbilitySystemComponent* TargetAS = ASI->GetAbilitySystemComponent();

		// Remove multiple effects
		TArray<FActiveGameplayEffectHandle*> ActiveHandles;
		ActiveEffectHandlers.MultiFindPointer(TargetAS, ActiveHandles);

		for (const auto& ActiveHandle : ActiveHandles)
			TargetAS->RemoveActiveGameplayEffect_NoReturn(*ActiveHandle, 1);

		ActiveEffectHandlers.Remove(TargetAS);
	}
}
