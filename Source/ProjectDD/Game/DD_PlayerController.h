// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DD_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API ADD_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ADD_PlayerController();
	virtual ~ADD_PlayerController() override;
	
	virtual void CreateTouchInterface() override;
	virtual void ActivateTouchInterface(UTouchInterface* NewTouchInterface) override;

	FORCEINLINE TObjectPtr<UTouchInterface> GetCurrentTouchInterface() const { return CurrentTouchInterface; }
	class SDD_VirtualJoyStick* GetVirtualJoyStick() const;
	
	FORCEINLINE void SetJoyStickVisualCenter(FVector2d Center) { JoyStickVisualCenter = Center; }
	FORCEINLINE FVector2d SetJoyStickVisualCenter() const { return JoyStickVisualCenter; }

	//FORCEINLINE DD_Handle GetUnitHandle() const { return UnitHandle; }
	//FORCEINLINE void SetUnitHandle(CY_Handle _UnitHandle) { UnitHandle = _UnitHandle; }
	//FORCEINLINE void ResetUnitHandle() { UnitHandle = InvalidUnitHandle; }
	
private:
	//CY_Handle UnitHandle = InvalidUnitHandle;
	
	FVector2d JoyStickVisualCenter = FVector2d();
};
