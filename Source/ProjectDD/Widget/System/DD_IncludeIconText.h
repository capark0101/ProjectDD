// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DD_Widget.h"
#include "DD_IncludeIconText.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UDD_IncludeIconText : public UDD_Widget
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
	TObjectPtr<class UImage> CPP_Icon = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_Text = nullptr;
};
