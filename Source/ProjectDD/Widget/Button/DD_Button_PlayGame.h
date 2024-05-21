// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DD_Button.h"
#include "DD_Button_PlayGame.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UDD_Button_PlayGame : public UDD_Button
{
	GENERATED_BODY()
public:
	virtual void SynchronizeProperties() override;

private:
	UPROPERTY(Category= "Icon & Text", EditAnywhere , Meta = (bAllowPrivateAccess = "true"))
	TObjectPtr<UTexture2D> IconImage = nullptr;

	UPROPERTY(Category= "Icon & Text", EditAnywhere , Meta = (bAllowPrivateAccess = "true"))
	FString Text;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_TitleText = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> CPP_Icon = nullptr;
    	
	UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> CPP_ResourceText = nullptr;
};
