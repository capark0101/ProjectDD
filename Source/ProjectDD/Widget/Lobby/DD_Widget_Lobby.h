// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DD_Widget.h"
#include "Data/DD_Data_Lobby.h"
#include "DD_Widget_Lobby.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UDD_Widget_Lobby : public UDD_Widget
{
	GENERATED_BODY()
public:
	virtual void InitWidget(const FName& TypeName, bool _bManaged, bool bActivate) override;
	virtual void FinishWidget() override;

	void InitLobby();
private:
	void InitTop();
	void InitLeftSide();
	void InitRightSide();
	void InitBottom();
	void InitCenter();
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> CPP_BGImage = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UDD_Widget_LobbyTop> CPP_LobbyTop = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UDD_Widget_LobbySide> CPP_LobbyLeft = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UDD_Widget_LobbySide> CPP_LobbyRight = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UDD_Widget_LobbyBottom> CPP_LobbyBottom = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UDD_Widget_LobbyCenter> CPP_LobbyCenter = nullptr;
	
	TWeakPtr<FDD_LobbyData> LobbyData = nullptr;
};
