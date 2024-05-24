// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_Widget_DialogScreenFader.h"
#include "DD_Define.h"

namespace FadeType
{
	const FName FadeIn = TEXT("FadeIn");
	const FName FadeOut = TEXT("FadeOut");
}

void UDD_Widget_DialogScreenFader::StartScreenFade(EDD_FadeType _FadeType, const TFunction<void()>& FadeCallback)
{
	FadeInCompleteCallback = nullptr;
	FadeOutCompleteCallback = nullptr;

	if(_FadeType == EDD_FadeType::FadeIn)
	{
		FadeInCompleteCallback = FadeCallback;
	}
	else if(_FadeType == EDD_FadeType::FadeOut)
	{
		FadeOutCompleteCallback = FadeCallback;
	}

	SetVisibility(ESlateVisibility::Visible);

	FadeType = _FadeType;
	if(FadeType == EDD_FadeType::FadeIn)
	{
		FadeStatus = EDD_FadeStatus::FadeInAnimation;
		PlayAnimationByName(FadeType::FadeIn);
	}
	else if(FadeType == EDD_FadeType::FadeOut)
	{
		FadeStatus = EDD_FadeStatus::FadeOutAnimation;
		PlayAnimationByName(FadeType::FadeOut);
	}
}

void UDD_Widget_DialogScreenFader::OnAnimFinished(const FName& AnimName)
{
	Super::OnAnimFinished(AnimName);

	if(AnimName == FadeType::FadeIn)
	{
		FinishedFadeIn();
	}
	else if(AnimName == FadeType::FadeOut)
	{
		FinishedFadeOut();
	}
}

void UDD_Widget_DialogScreenFader::FinishedFadeIn() const
{
	if(FadeInCompleteCallback)
	{
		FadeInCompleteCallback();
	}
	DD_LOG(TEXT("FadeIn Finished"));
}

void UDD_Widget_DialogScreenFader::FinishedFadeOut()
{
	if(FadeOutCompleteCallback)
	{
		FadeOutCompleteCallback();
	}
	DD_LOG(TEXT("FadeOut Finished"));
	
	SetVisibility(ESlateVisibility::Collapsed);
}
