// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_FadeSceneTool.h"

void UDD_FadeSceneTool::Initialize()
{
}

void UDD_FadeSceneTool::RegistLevelPath(uint8 SceneId)
{
}

void UDD_FadeSceneTool::Request(TObjectPtr<UDD_FadeCommand> Command)
{
}

void UDD_FadeSceneTool::FinishRequest()
{
}

void UDD_FadeSceneTool::Tick(float DeltaTime)
{
}

FString UDD_FadeSceneTool::GetLevelPath(EDD_GameSceneType SceneType)
{
	const FString* pLevelPath = LevelsPath.Find(static_cast<uint8>(SceneType));

	return pLevelPath ? *pLevelPath : FString();
}

void UDD_FadeSceneTool::StartFadeOut()
{
}

void UDD_FadeSceneTool::StartFadeIn()
{
}

void UDD_FadeSceneTool::PlayFadeAnimation(EDD_FadeStyle FadeType, bool bFadeIn, bool bDirectFadeIn)
{
}

void UDD_FadeSceneTool::PlayDrone(bool bIsFadeOut)
{
}

void UDD_FadeSceneTool::OnWidgetFadeOutFinished()
{
}

void UDD_FadeSceneTool::OnWidgetFadeInFinished()
{
}

void UDD_FadeSceneTool::OnCameraFadeOutFinished()
{
}

void UDD_FadeSceneTool::OnCameraFadeInFinished()
{
}
