// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DD_BuiltInWidgetTool.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UDD_BuiltInWidgetTool : public UObject
{
	GENERATED_BODY()

public:
	FORCEINLINE TObjectPtr<class UDD_Widget_DialogScreenFader> GetDialogScreenFader() const { return DialogScreenFader;}
	
	void BuiltInitialize();
	void Initialize();
	void Finalize();
	void Tick(float DeltaTime);

private:
	UPROPERTY()
	TObjectPtr<UDD_Widget_DialogScreenFader> DialogScreenFader = nullptr;
};
