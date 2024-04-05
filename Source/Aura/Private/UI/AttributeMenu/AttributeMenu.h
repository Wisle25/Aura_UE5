// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "UI/AuraUserWidgetBase.h"
#include "AttributeMenu.generated.h"

DECLARE_MULTICAST_DELEGATE(FAttributeOnClose);

class UButtonWidget;
class UTextRow;
class UTextRowButton;

UCLASS()
class UAttributeMenu : public UAuraUserWidgetBase
{
	GENERATED_BODY()

public:
	// ***===== Lifecycles =====*** //

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	// ***===== Events =====*** //

	FAttributeOnClose OnClose;

protected:
	// ***===== Widgets =====*** //

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButtonWidget> CloseBtn;

	UPROPERTY()
	TArray<TObjectPtr<UTextRowButton>> PrimaryRows;

	UPROPERTY()
	TArray<TObjectPtr<UTextRow>> SecondaryRows;

	void BindEvents();

	// ***===== Events =====*** //

	UFUNCTION()
	FORCEINLINE void Close()
	{
		SetVisibility(ESlateVisibility::Collapsed);
		OnClose.Broadcast();
	}

private:
	// ***===== Widgets =====*** //

	void GetTextRows();
};
