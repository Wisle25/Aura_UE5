// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS(Abstract)
class AURA_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacterBase();

protected:
	// ***===== Lifecycles =====*** //

	virtual void BeginPlay() override;

	// ***===== Combat =====*** //

	UPROPERTY(VisibleAnywhere, Category=Combat)
	TObjectPtr<USkeletalMeshComponent> Weapon;
};
