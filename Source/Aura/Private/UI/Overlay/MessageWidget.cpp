// Copyright, Wisle25

#include "UI/Overlay/MessageWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

//////////////////////////////////////////////////////////
// ==================== Lifecycles ==================== //

void UMessageWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // Hide for the first time
    SetVisibility(ESlateVisibility::Collapsed);    
}

//////////////////////////////////////////////////////////
// ==================== Attributes ==================== //

void UMessageWidget::PrepareMessage(UTexture2D* Image, FText Text, FVector2D ImageSize)
{
    if (Image)
    {
        FSlateBrush ImageBrush = UWidgetBlueprintLibrary::MakeBrushFromTexture(Image, ImageSize.X, ImageSize.Y);
        Icon   ->SetBrush(ImageBrush);
    }
    Message->SetText(Text);
    
    SetVisibility(ESlateVisibility::Visible);

    // Play animation for appearing and dissapearing with timer only when its not showing
    if (!bShowing)
    {
        PlayAnimationForward(Appear);
    }
    GetWorld()->GetTimerManager().SetTimer(DissapearTimerHandle, [this]() {
        PlayAnimationReverse(Appear);
    }, 3.f, false);
}

void UMessageWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
    if (Animation == Appear && bShowing)
        SetVisibility(ESlateVisibility::Collapsed);

    bShowing = !bShowing;
}
