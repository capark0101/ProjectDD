// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "DD_ButtonStyle_DefaultImage.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UDD_ButtonStyle_DefaultImage : public UCommonButtonStyle
{
	GENERATED_BODY()
public:
	void SetImage(UTexture2D* Texture);
};
