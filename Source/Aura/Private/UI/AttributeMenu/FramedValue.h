// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "UI/AuraUserWidgetBase.h"
#include "FramedValue.generated.h"

class UImage;
class UTextBlock;
class USizeBox;

UCLASS()
class UFramedValue : public UAuraUserWidgetBase
{
	GENERATED_BODY()

public:
	// ***===== Lifecycles ===== *** //

	virtual void NativePreConstruct() override;

	// ***===== Widgets =====*** //

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> ValueText;

};
