// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DD_Button.h"
#include "DD_Button_DefaultText.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UDD_Button_DefaultText : public UDD_Button
{
	GENERATED_BODY()
public:
	void SetNormalText(const FString& Text) const;
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCommonTextBlock> CPP_ButtonText = nullptr; 
};
