// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "UI/AuraUserWidgetBase.h"
#include "MessageWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class UMessageWidget : public UAuraUserWidgetBase
{
	GENERATED_BODY()

public:
	// ***===== Lifecycles =====*** //

	virtual void NativeConstruct() override;

	// ***===== Attributes =====*** //

	void PrepareMessage(UTexture2D* Image, FText Text, FVector2D ImageSize = { 75.f, 75.f });

protected:
	// ***===== Components =====*** //

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Icon;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Message;

	UPROPERTY(Transient, meta=(BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> Appear;

	// ***===== Attributes =====*** //

	FTimerHandle DissapearTimerHandle;

	bool bShowing = false;

	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;
};
