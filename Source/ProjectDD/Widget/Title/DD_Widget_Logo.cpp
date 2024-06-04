// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_Widget_Logo.h"

#include "DD_SceneManager.h"

void UDD_Widget_Logo::InitWidget(const FName& TypeName, bool _bManaged, bool bActivate)
{
	Super::InitWidget(TypeName, _bManaged, bActivate);
}

void UDD_Widget_Logo::FinishWidget()
{
	Super::FinishWidget();
}

void UDD_Widget_Logo::OnAnimFinished(const FName& AnimName)
{
	Super::OnAnimFinished(AnimName);

	if(AnimName == DefaultWidgetAnimation::Appearance)
	{
		PlayAnimationByName(DefaultWidgetAnimation::DisAppearance);
	}

	if(AnimName == DefaultWidgetAnimation::DisAppearance)
	{
		gSceneMng.ChangeScene(EDD_GameSceneType::Lobby);
	}
}