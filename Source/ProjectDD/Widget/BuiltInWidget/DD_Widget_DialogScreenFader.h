// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DD_Widget.h"
#include "DD_SceneDefine.h"
#include "DD_Widget_DialogScreenFader.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UDD_Widget_DialogScreenFader : public UDD_Widget
{
	GENERATED_BODY()

public:
	static FSoftObjectPath GetWidgetPath() { return FSoftObjectPath("/Game/UI/Widget/BuiltInWidget/DialogScreenFader.DialogScreenFader"); }
	
	void StartScreenFade(EDD_FadeType _FadeType, const TFunction<void()>& FadeCallback = nullptr);
	
protected:
	virtual void OnAnimFinished(const FName& AnimName) override;
	
private:
	void FinishedFadeIn() const;
	void FinishedFadeOut();
	
	EDD_FadeType FadeType;
	EDD_FadeStatus FadeStatus;

	TFunction<void()> FadeInCompleteCallback;
	TFunction<void()> FadeOutCompleteCallback;
};
