// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"

/**
 * 
 */

struct FDD_LobbySideData
{
	FString ButtonText = FString();
	UCommonButtonBase::FCommonButtonEvent ButtonEvent;
};

struct FDD_LobbyBottomData
{
	TObjectPtr<UTexture2D> ButtonImage = nullptr;
	UCommonButtonBase::FCommonButtonEvent ButtonEvent;
};

struct FDD_LobbyTopData
{
	TObjectPtr<UTexture2D> PlayerProfileIcon = nullptr;
	FString PlayerName = FString();
	float PlayerExp = 0.f;

	TArray<int32> ResourceItemIds;
};

struct FDD_LobbyCenterData
{
	
};

struct FDD_LobbyData
{
	// Top Part
	FDD_LobbyTopData TopData;
	
	// Side Part
	TArray<FDD_LobbySideData> LeftSideData;
	TArray<FDD_LobbySideData> RightSideData;
	
	// Bottom Part
	TArray<FDD_LobbyBottomData> BottomData;

	// Center Part
	FDD_LobbyCenterData CenterData;
};