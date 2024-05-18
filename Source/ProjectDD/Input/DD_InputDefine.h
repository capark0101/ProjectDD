// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"



UENUM(BlueprintType)
enum class EDD_Axis_Type : uint8
{
	Left	UMETA(DisplayName = "Axis_Type_Left"),
	Right	UMETA(DisplayName = "Axis_Type_Left"),
	Pinch	UMETA(DisplayName = "Axis_Type_Left"),
};

UENUM(BlueprintType)
enum class EDD_Action_Type : uint8
{
	ActionUpDown	UMETA(DisplayName = "Action_Type_UpDown"),
	ActionLeftRight	UMETA(DisplayName = "Action_Type_LeftRight"),
	Interaction		UMETA(DiaplayName = "Interaction"),
};

UENUM(BlueprintType)
enum class EDD_Touch_Event : uint8
{
	Down	UMETA(DisplayName = "Touch_Event_Down"),
	Up		UMETA(DisplayName = "Touch_Event_Up"),
	Move	UMETA(DisplayName = "Touch_Event_Move"),
};

UENUM(BlueprintType)
enum class EDD_AndroidButton_Type : uint8
{
	Back	UMETA(DisplayName = "AndroidButton_Back"),
	Menu	UMETA(DisplayName = "AndroidButton_Menu"),
};

DECLARE_DELEGATE_TwoParams(FBindAllKeysDelegate, const FKey&, bool);