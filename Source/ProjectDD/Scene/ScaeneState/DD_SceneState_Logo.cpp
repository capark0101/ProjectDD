// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_SceneState_Logo.h"

#include "DD_WidgetManager.h"
#include "Title/DD_Widget_Logo.h"

void UDD_SceneState_Logo::Begin()
{
	Super::Begin();

	gWidgetMng.DD_CreateWidget(UDD_Widget_Logo::GetWidgetName());
}

void UDD_SceneState_Logo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void UDD_SceneState_Logo::Exit()
{
	Super::Exit();
}
