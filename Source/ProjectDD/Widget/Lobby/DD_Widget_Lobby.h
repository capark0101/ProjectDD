// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DD_Widget.h"
#include "DD_Widget_Lobby.generated.h"

/**
 * 
 */

struct FDD_LobbyData
{
	// Side Part
	TArray<struct FDD_LobbySideData> LeftSideData;
	TArray<struct FDD_LobbySideData> RightSideData;
	
	// Bottom Part
	TArray<struct FDD_LobbyButtomData> BottomData;
};

struct FDD_LobbySideData
{
	FString ButtonText = FString();
	UCommonButtonBase::FCommonButtonEvent ButtonEvent;
};

struct FDD_LobbyBottomData
{
	TObjectPtr<UTexture2D> ButtonImage = nullptr;
	UCommonButtonBase::FCommonButtonEvent ButtonEvent;
};

UCLASS()
class PROJECTDD_API UDD_Widget_Lobby : public UDD_Widget
{
	GENERATED_BODY()
public:
	virtual void InitWidget(const FName& TypeName, bool _bManaged, bool bActivate) override;
	virtual void FinishWidget() override;

private:
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
};
