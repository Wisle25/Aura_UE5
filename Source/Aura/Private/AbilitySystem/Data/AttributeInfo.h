// Copyright, Wisle25

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AttributeInfo.generated.h"

USTRUCT(BlueprintType)
struct FAuraAttributeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag AttributeTag;

	UPROPERTY(EditDefaultsOnly)
	FText AttributeName;

	UPROPERTY(EditDefaultsOnly)
	FText AttributeDescription;

	UPROPERTY(VisibleAnywhere)
	float AttributeValue;
};

UCLASS()
class UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	FAuraAttributeInfo FindInfoForTag(const FGameplayTag& AttributeTag);

	UPROPERTY(EditDefaultsOnly)
	TArray<FAuraAttributeInfo> AttributeInfos;
};
