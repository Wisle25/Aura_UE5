// Copyright, Wisle25

#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindInfoForTag(const FGameplayTag& AttributeTag)
{
    for (const auto& Info : AttributeInfos)    
        if (Info.AttributeTag == AttributeTag)  
            return Info;

    return FAuraAttributeInfo();
}
