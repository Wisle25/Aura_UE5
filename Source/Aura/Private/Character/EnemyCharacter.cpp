// Copyright, Wisle25

#include "Character/EnemyCharacter.h"

AEnemyCharacter::AEnemyCharacter()
{
    // Mesh
    GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);  
    GetMesh()->SetCustomDepthStencilValue(250);

    // Weapon
    Weapon->SetCustomDepthStencilValue(250);
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
