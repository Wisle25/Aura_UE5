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

void UProgressGlobeBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (bChanging)
    {
        InterpGhostGlobe(InDeltaTime);
    }
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
    FProgressBarStyle GhostGlobeStyle;

    // Images
    ProgressBarStyle.BackgroundImage.TintColor = FColor(0.f); /* Make the alpha 0 as we dont need it */
    ProgressBarStyle.FillImage = ProgressFillBrush;

    GhostGlobeStyle.BackgroundImage.TintColor = FColor(0.f);
    GhostGlobeStyle.FillImage  = GhostGlobeBrush;

    GlobeProgressBar->SetWidgetStyle(ProgressBarStyle);
    GhostGlobe      ->SetWidgetStyle(GhostGlobeStyle);

    // Set padding for both globes
    UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(GlobeProgressBar->Slot);
    OverlaySlot->SetPadding(BoxPadding);

    OverlaySlot = Cast<UOverlaySlot>(GhostGlobe->Slot);
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
    const float SafeDivide = MaxValue == 0.f ? 1.f : MaxValue;
    bChanging        = true;
    GhostTarget      = Value / SafeDivide;

    GlobeProgressBar->SetPercent(GhostTarget);
}

void UProgressGlobeBase::InterpGhostGlobe(float DeltaTime)
{
    const float CurrentPercentage = GhostGlobe->GetPercent();
    const float InterpResult      = FMath::FInterpConstantTo(CurrentPercentage, GhostTarget, DeltaTime, 0.35f);
    GhostGlobe->SetPercent(InterpResult);

    // Stop the interp if already (or nearly) equal
    if (FMath::IsNearlyEqual(InterpResult, GhostTarget))
    {
        bChanging = false;

        // Make it perfect
        GhostGlobe->SetPercent(GhostTarget);
    }
}
