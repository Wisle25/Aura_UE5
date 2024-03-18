// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProgressGlobeBase.generated.h"

class UImage;
class UProgressBar;
class USizeBox;

UCLASS()
class UProgressGlobeBase : public UUserWidget
{
	GENERATED_BODY()

public:
	// ***===== Attributes =====*** //

	void SetPercentage(float Value, float MaxValue);

protected:
	// ***===== Lifecycles =====*** //

	virtual void NativePreConstruct() override;

	// ***===== Attributes =====*** //

	UPROPERTY(EditAnywhere, Category=Attributes)
	float BoxWidth;

	UPROPERTY(EditAnywhere, Category=Attributes)
	float BoxHeight;

	UPROPERTY(EditAnywhere, Category=Attributes)
	float BoxPadding;

	UPROPERTY(EditAnywhere, Category=Attributes)
	FSlateBrush ProgressFillBrush;

	UPROPERTY(EditAnywhere, Category=Attributes)
	FSlateBrush BGBrush;

	UPROPERTY(EditAnywhere, Category=Attributes)
	FSlateBrush GlassBrush;
	
	void InitBoxSize();
	void InitGlobe();
	void InitImageBrush();

	// ***===== Widgets =====*** //

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<USizeBox> Root_SizeBox;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> GlobeProgressBar;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Background;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Glass;
};
