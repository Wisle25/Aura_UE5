// Copyright, Wisle25

#include "UI/AttributeMenu/AttributeMenu.h"
#include "Components/Button.h"
#include "Controller/WidgetController/AttributeMenuController.h"
#include "UI/AttributeMenu/TextRowButton.h"
#include "UI/ButtonWidget.h"

//////////////////////////////////////////////////////////
// ==================== Lifecycles ==================== //

void UAttributeMenu::NativePreConstruct()
{
    Super::NativePreConstruct();

    GetTextRows();    
}

void UAttributeMenu::NativeConstruct()
{
    Super::NativeConstruct();

    SetVisibility(ESlateVisibility::Collapsed);
    BindEvents();
}

///////////////////////////////////////////////////////
// ==================== Widgets ==================== //

void UAttributeMenu::BindEvents()
{
    if (UAttributeMenuController* AttributeMenuController = Cast<UAttributeMenuController>(WidgetController))
    {
        // Primary
        for (int I = 0; I < 4; ++I)
        {
            AttributeMenuController->AttributeOnChange.AddUObject(PrimaryRows[I], &UTextRowButton::Prepare);
        }

        // Secondary
        for (int I = 0; I < 10; ++I)
        {
            AttributeMenuController->AttributeOnChange.AddUObject(SecondaryRows[I], &UTextRow::Prepare);
        }
    }

    // Buttons
    CloseBtn->Button->OnClicked.AddDynamic(this, &ThisClass::Close);
}

void UAttributeMenu::GetTextRows()
{
    // Primary
    for (int I = 0; I < 4; ++I)
    {
        const FName Name = *FString::Printf(TEXT("Primary%d"), I);
        UTextRowButton* TextRow = Cast<UTextRowButton>(GetWidgetFromName(Name));

        PrimaryRows.Add(TextRow);
    }

    // Secondary
    for (int I = 0; I < 10; ++I)
    {
        const FName Name = *FString::Printf(TEXT("Secondary%d"), I);
        UTextRow* TextRow = Cast<UTextRow>(GetWidgetFromName(Name));
        UE_LOG(LogTemp, Warning, TEXT("Secondary: %s"), TextRow ? *TextRow->GetName() : TEXT("None"))
        SecondaryRows.Add(TextRow);
    }
}
