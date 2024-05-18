// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DD_SceneDefine.h"
#include "DD_FadeSceneTool.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UDD_FadeSceneTool : public UObject
{
	GENERATED_BODY()
	
public:
	void Initialize();
	
	void RegistLevelPath(uint8 SceneId);
	
	void Request(TObjectPtr<class UDD_FadeCommand> Command);
	void FinishRequest();

	void Tick(float DeltaTime);
	FString GetLevelPath(EDD_GameSceneType SceneType);

private:
	void StartFadeOut();
	void StartFadeIn();

	void PlayFadeAnimation(EDD_FadeStyle FadeType, bool bFadeIn, bool bDirectFadeIn);
	void PlayDrone(bool bIsFadeOut = true);
	void OnWidgetFadeOutFinished();
	void OnWidgetFadeInFinished();

	void OnCameraFadeOutFinished();
	void OnCameraFadeInFinished();
	
	EDD_FadeStep CurrentStep = EDD_FadeStep::Ready;
	bool bLoadStart = false;
	bool bLoadComplete = false;

	float LoadingMinimumTime = 0.f;
	float LoadElapsedTime = 0.f;

	UPROPERTY()
	TMap<uint8, FString> LevelsPath;
	
	UPROPERTY()
	TArray<TObjectPtr<UDD_FadeCommand>> Commands;
	
	UPROPERTY()
	TObjectPtr<UDD_FadeCommand> FadeWidgetCommand = nullptr;
	
	//UPROPERTY()
	//TObjectPtr<class UDD_Widget_DialogScreenFader> DialogScreenFader = nullptr;

#define CREATE_FADE_COMMAND(CommandName) \
TObjectPtr<class UDD_FadeCommand> CommandName = DD_NewObject<UDD_FadeCommand>(); \
CommandName->AddToRoot(); \
CommandName->SetCreateFrom(__FILE__, __LINE__);
};
