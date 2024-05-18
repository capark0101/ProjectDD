// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "DD_Button.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UDD_Button : public UCommonButtonBase
{
	GENERATED_BODY()

public:
	UDD_Button();
	virtual ~UDD_Button() override;
	virtual void NativeConstruct() override;
	
	virtual void NativeOnCurrentTextStyleChanged() override;
	virtual const FText GetPaletteCategory() override;

	void SetOnClickedDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); DD_OnClickedDelegate = Delegate; }
	FORCEINLINE void UnbindClickedDelegate() { DD_OnClickedDelegate.Clear(); }
	void SetOnPressedDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); DD_OnPressedDelegate = Delegate; }
	FORCEINLINE void UnbindPressedDelegate() { DD_OnPressedDelegate.Clear(); }
	void SetOnReleasedDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); DD_OnReleasedDelegate = Delegate; }
	FORCEINLINE void UnbindReleasedDelegate() { DD_OnReleasedDelegate.Clear(); }
	void SetOnHoveredDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); DD_OnHoveredDelegate = Delegate; }
	FORCEINLINE void UnbindHoveredDelegate() { DD_OnHoveredDelegate.Clear(); }
	void SetOnUnhoveredDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); DD_OnUnhoveredDelegate = Delegate; };
	FORCEINLINE void UnbindUnhoveredDelegate() { DD_OnUnhoveredDelegate.Clear(); }
	void SetWillCloseWidgetDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); DD_WillCloseWidgetDelegate = Delegate; };
	FORCEINLINE void UnbindWillCloseWidgetDelegate() { DD_WillCloseWidgetDelegate.Clear(); }
	void SetWillCreateSceneDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); DD_WillCreateSceneDelegate = Delegate; };
	FORCEINLINE void UnbindWillCreateSceneDelegate() { DD_WillCreateSceneDelegate.Clear(); }
	void SetPlayAnimDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); DD_PlayAnimDelegate = Delegate; };
	FORCEINLINE void UnbindPlayAnimDelegate() { DD_PlayAnimDelegate.Clear(); }
	void SetOnClickedInDelayTimeDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); DD_OnClickedInDelayTimeDelegate = Delegate; };
	FORCEINLINE void UnbindClickedInDelayTimeDelegate() { DD_OnClickedInDelayTimeDelegate.Clear(); }
	void SetOnLongPressedDelegate(const FCommonButtonEvent& Delegate) { SetDelegates(); DD_OnLongPressedDelegate = Delegate; };
	FORCEINLINE void UnbindLongPressedDelegate() { DD_OnLongPressedDelegate.Clear(); }

	FORCEINLINE void SetCustomVector(const FVector& Vector) { CustomVector = Vector;}
	FORCEINLINE FVector GetCustomVector() const { return CustomVector; }
	
private:
	void SetDelegates();
	
	UFUNCTION() void OnClick();
	UFUNCTION() void OnPress();
	UFUNCTION() void OnRelease();
	UFUNCTION() void OnHover();
	UFUNCTION() void OnUnhover();

	FORCEINLINE bool IsUseClockedDelay() const { return bUseClickedDelay && 0.f < ClickedDelayTime; }
	FORCEINLINE bool IsUseLongPressedEvent() const { return bUseLongPressedEvent && 0.f < LongPressedTime && GetWorld() != nullptr; }
	
protected:	
	UPROPERTY(Category = UDD_Button, EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bUseClickedDelay = false;
	UPROPERTY(Category = UDD_Button, EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", EditCondition = "bUseClickedDelay"))
	float ClickedDelayTime = 0.f;
	UPROPERTY(Category = UDD_Button, EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bUseReleasedDelay = false;
	UPROPERTY(Category = UDD_Button, EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", EditCondition = "bUseReleasedDelay"))
	float ReleasedDelayTime = 0.f;
	UPROPERTY(Category = UDD_Button, EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bUseLongPressedEvent = false;
	UPROPERTY(Category = UDD_Button, EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", EditCondition = "bUseLongPressedEvent"))
	float LongPressedTime = 0.f;
	
	FCommonButtonEvent DD_OnClickedDelegate;
	FCommonButtonEvent DD_OnPressedDelegate;
	FCommonButtonEvent DD_OnReleasedDelegate;
	FCommonButtonEvent DD_OnHoveredDelegate;
	FCommonButtonEvent DD_OnUnhoveredDelegate;

	FCommonButtonEvent DD_OnClickedInDelayTimeDelegate;
	FCommonButtonEvent DD_OnLongPressedDelegate;

	FCommonButtonEvent DD_PlayAnimDelegate;
	FCommonButtonEvent DD_WillCloseWidgetDelegate;
	FCommonButtonEvent DD_WillCreateSceneDelegate;

	FTimerHandle PressTimerHandle;
	
	float LastClickedTime = 0.f;
	float LastReleasedTime = 0.f;

	FVector CustomVector = FVector::ZeroVector;
};
