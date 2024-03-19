// Copyright, Wisle25

#include "Effector/EffectorBase.h"
#include "Components/SphereComponent.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"

AEffectorBase::AEffectorBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// Interaction Sphere
	InteractionSphere = CreateDefaultSubobject<USphereComponent>("Collision Sphere");
	InteractionSphere->SetMobility(EComponentMobility::Static);
	InteractionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	InteractionSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	InteractionSphere->SetGenerateOverlapEvents(true);

	SetRootComponent(InteractionSphere);

	// Mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(InteractionSphere);
	Mesh->SetMobility(EComponentMobility::Static);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

//////////////////////////////////////////////////////////
// ==================== Lifecycles ==================== //

void AEffectorBase::BeginPlay()
{
	Super::BeginPlay();

	InitInteraction();
}

///////////////////////////////////////////////////////////
// ==================== Interaction ==================== //

void AEffectorBase::InitInteraction()
{
	InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnEnterInteraction);
	InteractionSphere->OnComponentEndOverlap  .AddDynamic(this, &ThisClass::OnLeaveInteraction);
}

void AEffectorBase::OnEnterInteraction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Only affecting if that target is implementing this interface
	if (IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(OtherActor))	
	{
		ApplyEffectTo(ASI);
		Destroy();
	}
}

void AEffectorBase::OnLeaveInteraction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void AEffectorBase::ApplyEffectTo(IAbilitySystemInterface* Target)
{
	// NOTE: AS is Ability System
	UAbilitySystemComponent* TargetAS = Target->GetAbilitySystemComponent();

	FGameplayEffectContextHandle CtxHandle = TargetAS->MakeEffectContext();
	CtxHandle.AddSourceObject(this);

	const FGameplayEffectSpecHandle EffectSpec = TargetAS->MakeOutgoingSpec(GameplayEffectClass, 1.f, CtxHandle);
	TargetAS->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data.Get());
}
