// Copyright, Wisle25

#include "UI/AttributeMenu/TextRow.h"
#include "UI/AttributeMenu/FramedValue.h"
#include "Components/TextBlock.h"
#include "AbilitySystem/Data/AttributeInfo.h"

//////////////////////////////////////////////////////////
// ==================== Widgets ==================== //

void UTextRow::Prepare(const FAuraAttributeInfo& Info)
{
    if (!AttributeTag.MatchesTagExact(Info.AttributeTag)) return;
    
    Label->SetText(Info.AttributeName);
    Value->ValueText->SetText(
        FText::FromString(
            FString::Printf(TEXT("%d"), FMath::FloorToInt(Info.AttributeValue))
        )
    );
}
