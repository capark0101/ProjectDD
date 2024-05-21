// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DD_Widget.h"
#include "DD_Widget_Profile.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UDD_Widget_Profile : public UDD_Widget
{
	GENERATED_BODY()
public:
	void SetProfileData(const FString& PlayerName, float PlayerExp, const TObjectPtr<UTexture2D>& PlayerProfileIcon);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> CPP_PlayerProfileIcon = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_PlayerName = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_PlayerLevel = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> CPP_PlayerRemainExp = nullptr;
};
