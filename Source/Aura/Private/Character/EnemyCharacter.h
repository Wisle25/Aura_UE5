// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "Interfaces/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class AEnemyCharacter : public ACharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	
public:
	AEnemyCharacter();

	// ***===== Enemy Interaction =====*** //

	virtual void Highlight() override;
	virtual void UnHighlight() override;
};
