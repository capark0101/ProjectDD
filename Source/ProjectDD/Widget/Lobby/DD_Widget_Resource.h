// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DD_Widget.h"
#include "DD_Widget_Resource.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UDD_Widget_Resource : public UDD_Widget
{
	GENERATED_BODY()
public:
	void InitResourceData(int32 ResourceItemId);
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> CPP_ResourceImage = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_ResourceRemainCount = nullptr;
};
