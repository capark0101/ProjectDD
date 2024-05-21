// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_Widget_LobbyTop.h"

#include "DD_Widget_Lobby.h"
#include "DD_Widget_Profile.h"
#include "DD_Widget_Resource.h"

void UDD_Widget_LobbyTop::InitWidget(const FName& TypeName, bool _bManaged, bool bActivate)
{
	Super::InitWidget(TypeName, _bManaged, bActivate);

	ResourceWidgets.Empty();
	ResourceWidgets.Emplace(CPP_ResourceWidget_1);
	ResourceWidgets.Emplace(CPP_ResourceWidget_2);
	ResourceWidgets.Emplace(CPP_ResourceWidget_3);
}

void UDD_Widget_LobbyTop::FinishWidget()
{
	Super::FinishWidget();
}


void UDD_Widget_LobbyTop::SetTopData(const FDD_LobbyTopData& TopData) const
{
	CPP_ProfileWidget->SetProfileData(TopData.PlayerName, TopData.PlayerExp, TopData.PlayerProfileIcon);

	for(int32 i = 0  ; i < TopData.ResourceItemIds.Num() ; i++)
	{
		if(ResourceWidgets.IsValidIndex(i) && TopData.ResourceItemIds.IsValidIndex(i))
		{
			ResourceWidgets[i]->InitResourceData(TopData.ResourceItemIds[i]);
		}
	}
}