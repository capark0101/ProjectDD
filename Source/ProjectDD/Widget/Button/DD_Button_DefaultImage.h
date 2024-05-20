// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DD_Button.h"
#include "DD_Button_DefaultImage.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UDD_Button_DefaultImage : public UDD_Button
{
	GENERATED_BODY()
public:
	void SetNormalTexture(UTexture2D* Texture);
};
