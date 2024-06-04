// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_SceneState_Lobby.h"

#include "DD_WidgetManager.h"
#include "Lobby/DD_Widget_Lobby.h"

void UDD_SceneState_Lobby::Begin()
{
	Super::Begin();

	gWidgetMng.DD_CreateWidget(UDD_Widget_Lobby::GetWidgetName());
}

void UDD_SceneState_Lobby::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void UDD_SceneState_Lobby::Exit()
{
	Super::Exit();
}
