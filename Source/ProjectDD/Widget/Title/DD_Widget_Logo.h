// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DD_Widget.h"
#include "DD_Widget_Logo.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UDD_Widget_Logo : public UDD_Widget
{
	GENERATED_BODY()

public:
	static FName GetWidgetName() { return TEXT("Logo"); }

	virtual void InitWidget(const FName& TypeName, bool _bManaged, bool bActivate) override;
	virtual void FinishWidget() override;

	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;
};
