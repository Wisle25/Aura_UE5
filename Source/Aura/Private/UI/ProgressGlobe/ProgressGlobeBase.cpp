// Copyright, Wisle25

#include "UI/ProgressGlobe/ProgressGlobeBase.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/SizeBox.h"
#include "Components/OverlaySlot.h"

//////////////////////////////////////////////////////////
// ==================== Lifecycles ==================== //

void UProgressGlobeBase::NativePreConstruct()
{
    Super::NativePreConstruct();
    
    InitBoxSize();    
    InitGlobe();
    InitImageBrush();
}

//////////////////////////////////////////////////////////
// ==================== Attributes ==================== //

void UProgressGlobeBase::InitBoxSize()
{
    Root_SizeBox->SetWidthOverride(BoxWidth);
    Root_SizeBox->SetHeightOverride(BoxHeight);
}

void UProgressGlobeBase::InitGlobe()
{
    FProgressBarStyle ProgressBarStyle;

    // Images
    ProgressBarStyle.BackgroundImage.TintColor = FColor(0.f, 0.f, 0.f, 0.f); /* Make the alpha 0 as we dont need it */
    ProgressBarStyle.FillImage = ProgressFillBrush;

    GlobeProgressBar->SetWidgetStyle(ProgressBarStyle);    

    // Set padding
    UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(GlobeProgressBar->Slot);
    OverlaySlot->SetPadding(BoxPadding);
}

void UProgressGlobeBase::InitImageBrush()
{
    // Background
    Background->SetBrush(BGBrush);

    // Glass
    Glass->SetBrush(GlassBrush);
}

void UProgressGlobeBase::SetPercentage(float Value, float MaxValue)
{
    float SafeDivide = MaxValue == 0.f ? 1.f : MaxValue;

    GlobeProgressBar->SetPercent(Value / SafeDivide);
}
