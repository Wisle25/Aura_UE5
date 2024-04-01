// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "EffectorBase.generated.h"

class IAbilitySystemInterface;
class UBoxComponent;
class UGameplayEffect;
class USphereComponent;
class UNiagaraComponent;
class UAbilitySystemComponent;

/** At what time the effector should affect the target */
UENUM()
enum class EApplyWhen : uint8
{
	EAW_BeginOverlap UMETA(DisplayName="Begin Overlapping"),
	EAW_EndOverlap	 UMETA(DisplayName="End Overlapping")
};

UENUM()
enum class ERemoveWhen : uint8
{
	ERW_EndOverlap   UMETA(DisplayName="End Overlapping"),
	DoNotRemove
};

UENUM()
enum class EVisualType : uint8
{
	EVT_Mesh     UMETA(DisplayName="By Mesh"),
	EVT_Particle UMETA(DisplayName="By Particle")
};

UENUM()
enum class EInteractingWith : uint8
{
	EIW_Sphere UMETA(DisplayName="With Sphere"),
	EIW_Box	   UMETA(DisplayName="With Box")
};

UCLASS(Abstract)
class AEffectorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AEffectorBase();

protected:
	// ***===== Lifecycles =====*** //

	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;

	// ***===== Components =====*** //

	//* Those enums are for determining which interaction and/or visualy by *//

	UPROPERTY(EditAnywhere, Category=Components)
	EVisualType VisualType = EVisualType::EVT_Mesh;

	UPROPERTY(EditAnywhere, Category=Components)
	EInteractingWith InteractingWith = EInteractingWith::EIW_Sphere;

	void DetermineComponents();

	// * Actual Components * //

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> InteractionSphere;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> InteractionBox;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;

	/** Use this instead of mesh if the visual is just particle */
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> Particle;

	// ***===== Interaction =====*** //

	UPROPERTY(EditAnywhere, Category=Interaction)
	TArray<TSubclassOf<UGameplayEffect>> GameplayEffectClasses;

	UPROPERTY(EditAnywhere, Category=Interaction)
	EApplyWhen ApplyWhen = EApplyWhen::EAW_BeginOverlap;

	UPROPERTY(EditAnywhere, Category=Interaction)
	ERemoveWhen RemoveWhen = ERemoveWhen::DoNotRemove;

	TMultiMap<UAbilitySystemComponent*, FActiveGameplayEffectHandle> ActiveEffectHandlers; 

	/** Should the effector get destroyed right after applied the gameplay effect? */
	UPROPERTY(EditAnywhere, Category=Interaction)
	bool bInstantDestroy = true;

	void InitInteraction();

	UFUNCTION()
	void OnEnterInteraction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnLeaveInteraction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void ApplyEffectTo(AActor* Target);
	void RemoveEffectFrom(AActor* Target);
};
