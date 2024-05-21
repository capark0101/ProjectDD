// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_Widget_Lobby.h"

#include "DD_Widget_LobbyBottom.h"
#include "DD_Widget_LobbyCenter.h"
#include "DD_Widget_LobbySide.h"
#include "DD_Widget_LobbyTop.h"

void UDD_Widget_Lobby::InitWidget(const FName& TypeName, bool _bManaged, bool bActivate)
{
	Super::InitWidget(TypeName, _bManaged, bActivate);
}

void UDD_Widget_Lobby::FinishWidget()
{
	Super::FinishWidget();
}

void UDD_Widget_Lobby::InitLobby()
{
	// Step1. Top Property
	InitTop();

	// Step2. Side Property(Left)
	InitLeftSide();

	// Step3. Side Property(Right)
	InitRightSide();

	// Step4. Bottom Property
	InitBottom();

	// Step5. Center Property
	InitCenter();
}

void UDD_Widget_Lobby::InitTop()
{
	
	if(LobbyData.IsValid() == false)
	{
		return;
	}
	//CPP_LobbyTop->SetScrollBox(LobbyData.Pin().Get()->TopData);
}

void UDD_Widget_Lobby::InitLeftSide()
{
	
	if(LobbyData.IsValid() == false)
	{
		return;
	}

	CPP_LobbyLeft->SetScrollBox(LobbyData.Pin().Get()->LeftSideData);
}

void UDD_Widget_Lobby::InitRightSide()
{
	
	if(LobbyData.IsValid() == false)
	{
		return;
	}
	
	CPP_LobbyRight->SetScrollBox(LobbyData.Pin().Get()->RightSideData);
}

void UDD_Widget_Lobby::InitBottom()
{
	if(LobbyData.IsValid() == false)
	{
		return;
	}
	
	CPP_LobbyBottom->SetScrollBox(LobbyData.Pin().Get()->BottomData);
}

void UDD_Widget_Lobby::InitCenter()
{
	if(LobbyData.IsValid() == false)
	{
		return;
	}

	CPP_LobbyCenter->InitCenterData(LobbyData.Pin().Get()->CenterData);
}
