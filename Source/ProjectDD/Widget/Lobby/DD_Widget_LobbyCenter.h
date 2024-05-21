// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DD_Widget.h"
#include "Data/DD_Data_Lobby.h"
#include "DD_Widget_LobbyCenter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UDD_Widget_LobbyCenter : public UDD_Widget
{
	GENERATED_BODY()
public:
	void InitCenterData(const FDD_LobbyCenterData& CenterData);

private:
	
};
