// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DD_Widget.h"
#include "DD_Widget_LobbyBottom.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UDD_Widget_LobbyBottom : public UDD_Widget
{
	GENERATED_BODY()
public:
	void SetScrollBox(TArray<struct FDD_LobbyBottomData> ButtonData) const;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UScrollBox> CPP_ButtonScrollBox = nullptr;
};
