// Copyright, Wisle25

#include "Character/CharacterBase.h"
#include "AbilitySystemComponent.h"

ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// Weapon
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), "WeaponHandSocket");
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

//////////////////////////////////////////////////////////
// ==================== Attributes ==================== //

void ACharacterBase::ApplyEffectToSelf(const TSubclassOf<UGameplayEffect> EffectClass, float Level) const
{
	check(GetAbilitySystemComponent());
	check(EffectClass);

	FGameplayEffectContextHandle CtxHandle = GetAbilitySystemComponent()->MakeEffectContext();
	FGameplayEffectSpecHandle   SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(EffectClass, Level, CtxHandle);
	CtxHandle.AddSourceObject(this);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void ACharacterBase::InitDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes);
	ApplyEffectToSelf(DefaultSecondaryAttributes);
	ApplyEffectToSelf(DefaultVitalAttributes);
}
