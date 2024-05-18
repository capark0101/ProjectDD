// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/TouchInterface.h"
#include "DD_TouchInterface.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UDD_TouchInterface : public UTouchInterface
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Image")
	TObjectPtr<UTexture2D> ImageCenter = nullptr;

	UPROPERTY(EditAnywhere, Category = "Image")
	FVector2D CenterImageSize = FVector2D(100.0f, 100.0f);

	UPROPERTY(EditAnywhere, Category = "Image")
	float CenterImageOpacity = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Image")
	TObjectPtr<UTexture2D> ImageOuter = nullptr;

	UPROPERTY(EditAnywhere, Category = "Image")
	FVector2D OuterImageSize = FVector2D(100.0f, 100.0f);

	UPROPERTY(EditAnywhere, Category = "Image")
	float OuterImageOpacity = 1.0f;
};
