// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonWidget.generated.h"

class UButton;
class USizeBox;
class UTextBlock;

UCLASS()
class UButtonWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// ***===== Lifecycles =====*** //

	virtual void NativePreConstruct() override;

	// ***===== Attributes =====*** //

	/** Height and Width */
	UPROPERTY(EditAnywhere, Category=Attributes)
	FVector2D Dimension = { 50.f, 50.f };

	UPROPERTY(EditAnywhere, Category=Attributes)
	FButtonStyle ButtonStyle;

	UPROPERTY(EditAnywhere, Category=Attributes)
	FSlateFontInfo TextFont;

	UPROPERTY(EditAnywhere, Category=Attributes)
	FText TextBtn = FText::FromString(TEXT("X"));

	/** Applying attributes to the widget */
	void PrepareWidget();

	// ***===== Components =====*** //

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<USizeBox> Root;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Button;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Text;
};
