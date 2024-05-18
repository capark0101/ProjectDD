// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DD_Singleton.h"
#include "Input/DD_InputDefine.h"
#include "UObject/Object.h"
#include "DD_InputManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UDD_InputManager : public UObject, public TDD_Singleton<UDD_InputManager>
{
	GENERATED_BODY()

public:
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Tick(float _DeltaTime) override;

	void RegistAxis(EDD_Axis_Type AxisType, EDD_Action_Type ActionType, const FInputAxisUnifiedDelegate& Event);
	void RegistTouch(EDD_Touch_Event TouchEventType, const FInputTouchBinding& Event);
	void RegistAndroidButton(EDD_AndroidButton_Type ButtonType, const FSimpleDelegate& Delegate);
	
	void CreateInputPawn();
	void DestroyInputPawn();

	FORCEINLINE FBindAllKeysDelegate& GetBindAllKeysDelegate() { return AllKeysDelegate; }

private:
	UPROPERTY()
	TObjectPtr<class ADD_Input> InputPawn = nullptr;

	FBindAllKeysDelegate AllKeysDelegate;

	// todo : 용섭 Input Mapping Part
	
public:
	void LeftAxisUpDown(float Value);
	void LeftAxisLeftRight(float Value);
	void RightAxisUpDown(float Value);
	void RightAxisLeftRight(float Value);
	
	void OnTouchDown(const ETouchIndex::Type FingerIndex, const FVector Location);
	void OnTouchUp(const ETouchIndex::Type FingerIndex, const FVector Location);
	void OnTouchMove(const ETouchIndex::Type FingerIndex, const FVector Location);
	void AndroidBack();
	void AndroidMenu();

private:
	FInputAxisBinding CharacterMove_UpDownEvent = FInputAxisBinding(TEXT("CharacterMove_UpDown"));
	FInputAxisBinding CharacterMove_LeftRightEvent = FInputAxisBinding(TEXT("CharacterMove_LeftRight"));
	FInputAxisBinding CameraMove_UpDownEvent = FInputAxisBinding(TEXT("CameraMove_UpDown"));
	FInputAxisBinding CameraMove_LeftRightEvent = FInputAxisBinding(TEXT("CameraMove_LeftRight"));
	
	FInputTouchBinding TouchDownEvent = FInputTouchBinding(IE_Pressed);
	FInputTouchBinding TouchUpEvent = FInputTouchBinding(IE_Released);
	FInputTouchBinding TouchMoveEvent = FInputTouchBinding(IE_Repeat);
	FSimpleDelegate AndroidBackDelegate;
	FSimpleDelegate AndroidMenuDelegate;

	FSimpleDelegate InteractionDelegate;
	FSimpleDelegate WorldMapDelegate;
	
#define gInputMng (*UDD_InputManager::GetInstance())
	
};
