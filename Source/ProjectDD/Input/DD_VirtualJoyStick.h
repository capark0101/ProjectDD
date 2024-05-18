// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Input/SVirtualJoystick.h"

/**
 * 
 */
class PROJECTDD_API SDD_VirtualJoyStick : public SVirtualJoystick
{
public:
	TSharedPtr<ISlateBrushSource> ImageCenter;
	FVector2d CenterImageSize;
	float CenterImageOpacity;

	TSharedPtr<ISlateBrushSource> ImageOuter;
	FVector2d OuterImageSize;
	float OuterImageOpacity;

	FVector2d Center;
	FVector2d VisualSize;
	FVector2d InteractionSize;
	FVector2d ThumbSize;
	FVector2d InputScale;

	bool bSendOneMoreEvent;
	FVector2d CurrentNormalizeOffset;
	FVector2d CurrentNormalizeOffset_Image;

	FORCEINLINE FVector2d GetVisualCenter() const { return VisualCenter; }

public:
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	virtual FReply OnTouchStarted(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override;
	virtual FReply OnTouchMoved(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override;
	virtual FReply OnTouchEnded(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override;
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
	virtual bool HandleTouch(int32 ControlIndex, const FVector2D& LocalCoordinate, const FVector2D& ScreenSize) override;
	virtual void HandleDisplayMetricsChanged(const FDisplayMetrics& NewDisplayMetric) override;

	static bool IsActiveJoyStick();

	FVector2d ThumbPosition;
	FVector2d VisualCenter;
	FVector2d CorrectedCenter;
	FVector2d CorrectedVisualSize;
	FVector2d CorrectedInteractionSize;
	FVector2d CorrectedThumbSize;
	FVector2d CorrectedInputScale;
	FVector2d CorrectedCenterImageSize;
	FVector2d CorrectedOuterImageSize;

	int32 CapturePointerIndex = -1;
	FVector2d NextCenter;
	bool bHasBeenPosited = false;

	float PreviousScalingFactor = 0.f;
	FVector2d JoyStickDist;
};
