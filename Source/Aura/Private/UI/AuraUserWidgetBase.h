// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidgetBase.generated.h"

class UWidgetControllerBase;

UCLASS()
class UAuraUserWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	// ***===== References =====*** //

	void SetWidgetController(UWidgetControllerBase* InController);

protected:
	// ***===== References =====*** //

	UPROPERTY()	
	TWeakObjectPtr<UWidgetControllerBase> WidgetController;
};
