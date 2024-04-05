// Copyright, Wisle25

#include "UI/ButtonWidget.h"
#include "Components/Button.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"

//////////////////////////////////////////////////////////
// ==================== Lifecycles ==================== //

void UButtonWidget::NativePreConstruct()
{
    Super::NativePreConstruct();

    PrepareWidget();
}

//////////////////////////////////////////////////////////
// ==================== Attributes ==================== //

void UButtonWidget::PrepareWidget()
{
    Root->SetWidthOverride (Dimension.X);
    Root->SetHeightOverride(Dimension.Y);
    Button->SetStyle(ButtonStyle);
    Text->SetText(TextBtn);
    Text->SetFont(TextFont);
}
