// Copyright, Wisle25

#include "Character/EnemyCharacter.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AEnemyCharacter::AEnemyCharacter()
{
    // Mesh
    GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);  
    GetMesh()->SetCustomDepthStencilValue(250);

    // Weapon
    Weapon->SetCustomDepthStencilValue(250);

    // Ability System
    AbilitySystem = CreateDefaultSubobject<UAuraAbilitySystemComponent>("Ability System");
    AbilitySystem->SetIsReplicated(true);
    AbilitySystem->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

    // Attribute Set
    AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("Attribute Set");
}

//////////////////////////////////////////////////////////
// ==================== Lifecycles ==================== //

void AEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();

    // ...
    AbilitySystem->InitAbilityActorInfo(this, this);
    AbilitySystem->AbilitySystemOnSet();
}

///////////////////////////////////////////////////////////
// ==================== Enemy Interaction ==================== //

void AEnemyCharacter::Highlight()
{
    GetMesh()->SetRenderCustomDepth(true);
    Weapon   ->SetRenderCustomDepth(true);
}

void AEnemyCharacter::UnHighlight()
{
    GetMesh()->SetRenderCustomDepth(false);
    Weapon   ->SetRenderCustomDepth(false);
}

UAbilitySystemComponent* AEnemyCharacter::GetAbilitySystemComponent() const 
{
    return AbilitySystem;
}
