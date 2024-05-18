// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DD_SceneDefine.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EDD_GameSceneType : uint8
{
	None = 0	UMETA(DisplayName = "None"),
	Logo		UMETA(DisplayName = "Logo"),
	Title		UMETA(DisplayName = "Title"),
};

UENUM(BlueprintType)
enum class EDD_GameCameraType : uint8
{
	None = 0	UMETA(DisplayName = "None"),
	Title		UMETA(DisplayName = "Title"),
};

enum class EDD_ChangeSceneStep
{
	Ready = 0,
	PlayFade,
	StartLoadLevel,
	PrepareSceneState,
	Complete,
};

USTRUCT()
struct FDD_ChangeSceneData
{
	GENERATED_USTRUCT_BODY()

	EDD_GameSceneType SceneType;
	EDD_ChangeSceneStep Step;
	FName LevelPackagePath;
};

enum class EDD_FadeType
{
	None = 0,
	FadeIn,
	FadeOut,
};

enum class EDD_FadeStatus
{
	None = 0,
	FadeInAnimation,
	FadeOutAnimation,
};

enum class EDD_FadeStep
{
	Ready = 0,
	EnterFadeOut,
	ExitFadeOut,
	EnterFadeIn,
	ExitFadeIn,
};

enum class EDD_FadeStyle
{
	None = 0,
	Dialog,
	Drone,
	ForceDroneFadeIn,
};

enum class EDD_LoadingPageType
{
	None = 0,
	EnterFirst,
	ShowWorldMap,
};

DECLARE_DELEGATE_OneParam(FDD_LoadLevelInitialized, const FString&);
DECLARE_MULTICAST_DELEGATE_OneParam(FDD_ChangeSceneDelegate, EDD_GameSceneType);
DECLARE_MULTICAST_DELEGATE_OneParam(FDD_LoadLevelDelegate, const FString&);
DECLARE_MULTICAST_DELEGATE_OneParam(FDD_ChangeSceneState, uint8);