// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "Controller/WidgetController/WidgetControllerBase.h"
#include "GameplayTagContainer.h"
#include "OverlayWidgetController.generated.h"

class UAuraUserWidgetBase;

USTRUCT()
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FGameplayTag MessageTag;

	UPROPERTY(EditAnywhere)
	FText Message;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UTexture2D> Image;
};

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, float);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnManaChanged, float, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FMessageWidget, FUIWidgetRow);

UCLASS()
class UOverlayWidgetController : public UWidgetControllerBase
{
	GENERATED_BODY()

public:
	UOverlayWidgetController();

	// ***===== References =====*** //

	virtual void BroadcastInitialValues() override;
	virtual void BindOnChanges() override;

	// ***===== GAS Attributes =====*** //

	FOnHealthChanged OnHealthChanged;
	FOnManaChanged OnManaChanged;

	/** Will be broadcasted when specified gameplay tag is applied */
	FMessageWidget MessageWidget;

protected:
	// ***===== Data =====*** //

	UPROPERTY(EditDefaultsOnly, Category=WidgetData)
	TWeakObjectPtr<UDataTable> MessageWidgetData;
};
