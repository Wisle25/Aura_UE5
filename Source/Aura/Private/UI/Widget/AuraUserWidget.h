// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

class UWidgetController;

UCLASS()
class UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	// ***===== References =====*** //

	UPROPERTY()	
	TWeakObjectPtr<UWidgetController> WidgetController;
};
