// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EffectorBase.generated.h"

class IAbilitySystemInterface;
class UGameplayEffect;
class USphereComponent;

UCLASS(Abstract)
class AEffectorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AEffectorBase();

protected:
	// ***===== Lifecycles =====*** //

	virtual void BeginPlay() override;

	// ***===== Components =====*** //

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> InteractionSphere;

	// ***===== Interaction =====*** //

	UPROPERTY(EditAnywhere, Category=Interaction)
	TSubclassOf<UGameplayEffect> GameplayEffectClass;

	void InitInteraction();

	UFUNCTION()
	void OnEnterInteraction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnLeaveInteraction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void ApplyEffectTo(IAbilitySystemInterface* Target);
};
