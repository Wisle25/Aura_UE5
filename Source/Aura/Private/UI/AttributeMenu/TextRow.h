// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayTagContainer.h"
#include "TextRow.generated.h"

class UFramedValue;
class UTextBlock;
struct FAuraAttributeInfo;

UCLASS()
class UTextRow : public UUserWidget
{
	GENERATED_BODY()

public:
	// ***===== Widgets =====*** //

	virtual void Prepare(const FAuraAttributeInfo& Info);

protected:

	// ***===== Attributes =====*** //

	UPROPERTY(EditAnywhere, Category=Attributes)
	FGameplayTag AttributeTag;

	// ***===== Widgets =====*** //

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Label;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UFramedValue> Value;
};
