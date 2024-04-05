// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "Controller/WidgetController/WidgetControllerBase.h"
#include "AttributeMenuController.generated.h"

class UAttributeInfo;
struct FGameplayTag;
struct FGameplayAttribute;
struct FAuraAttributeInfo;

DECLARE_MULTICAST_DELEGATE_OneParam(FAttributeInfoOnChange, const FAuraAttributeInfo&);

UCLASS()
class UAttributeMenuController : public UWidgetControllerBase
{
	GENERATED_BODY()

public:
	UAttributeMenuController();

	// ***===== WidgetControllerBase =====*** //
    virtual void BroadcastInitialValues() override;
    virtual void BindOnChanges() override;
    // ***===== End WidgetControllerBase =====*** //

    // ***===== Attributes =====*** //

    FAttributeInfoOnChange AttributeOnChange;

protected:
	UPROPERTY(EditDefaultsOnly, Category=Attribute)
	TObjectPtr<UAttributeInfo> AttributeInfo;

private:
	void InitAsset();
    void BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const;
};
