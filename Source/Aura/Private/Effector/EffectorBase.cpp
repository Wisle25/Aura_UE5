// Copyright, Wisle25

#include "Effector/EffectorBase.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"

AEffectorBase::AEffectorBase()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root Scene");
	RootComponent->SetMobility(EComponentMobility::Static);

	// Interaction Sphere
	InteractSphere = CreateDefaultSubobject<USphereComponent>("Collision Sphere");
	InteractSphere->SetupAttachment(RootComponent);
	InteractSphere->SetMobility(EComponentMobility::Static);
	InteractSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	InteractSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	InteractSphere->SetGenerateOverlapEvents(true);

	// Interaction Box
	InteractBox = CreateDefaultSubobject<UBoxComponent>("Collision Box");
	InteractBox->SetupAttachment(RootComponent);
	InteractBox->SetMobility(EComponentMobility::Static);
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

//////////////////////////////////////////////////////////
// ==================== Lifecycles ==================== //

void AEffectorBase::OnConstruction(const FTransform& Transform)
{
	DetermineComponents();
}

void AEffectorBase::BeginPlay()
{
	Super::BeginPlay();

	InitInteraction();
}

//////////////////////////////////////////////////////////
// ==================== Components ==================== //

void AEffectorBase::DetermineComponents()
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

	// Interacting With
	switch (InteractingWith)
	{
	case EInteractingWith::EIW_Box:
		if (InteractSphere) InteractSphere->DestroyComponent();
		break;
	
	case EInteractingWith::EIW_Sphere:
		if (InteractBox) InteractBox->DestroyComponent();
		break;
	}
}

///////////////////////////////////////////////////////////
// ==================== Interaction ==================== //

void AEffectorBase::InitInteraction()
{
	if (InteractSphere)
	{
		InteractSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnEnterInteraction);
		InteractSphere->OnComponentEndOverlap  .AddDynamic(this, &ThisClass::OnLeaveInteraction);
	}

	if (InteractBox)
	{
		InteractBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnEnterInteraction);
		InteractBox->OnComponentEndOverlap  .AddDynamic(this, &ThisClass::OnLeaveInteraction);
	}
}

void AEffectorBase::OnEnterInteraction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Applying
	if (ApplyWhen == EApplyWhen::EAW_BeginOverlap)
		ApplyEffectTo(OtherActor);
}

void AEffectorBase::OnLeaveInteraction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Applying
	if (ApplyWhen == EApplyWhen::EAW_EndOverlap)
		ApplyEffectTo(OtherActor);
	
	// Removing
	if (RemoveWhen == ERemoveWhen::ERW_EndOverlap)
		RemoveEffectFrom(OtherActor);		
}

void AEffectorBase::ApplyEffectTo(AActor* Target)
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

void AEffectorBase::RemoveEffectFrom(AActor* Target)
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
