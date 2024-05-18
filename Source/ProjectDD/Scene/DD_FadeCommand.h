// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DD_SceneDefine.h"
#include "DD_FadeCommand.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(FDD_FadeEventDelegate);
DECLARE_DELEGATE_RetVal(bool, FDD_FadeCheckLoadDelegate);

UCLASS()
class PROJECTDD_API UDD_FadeCommand : public UObject
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetFadeStyle(EDD_FadeStyle FadeStyle) { Fade = FadeStyle; }
	FORCEINLINE void SetIsDirectFadeOut(bool _bDirectFadeOut) { bDirectFadeOut = _bDirectFadeOut; }
	FORCEINLINE void SetLoadingPageType(EDD_LoadingPageType Type) { LoadingPageType = Type; }
	
	FORCEINLINE EDD_FadeStyle GetFadeType() const { return Fade; }
	FORCEINLINE bool GetIsDirectFadeOut() const { return bDirectFadeOut; }
	FORCEINLINE EDD_LoadingPageType GetLoadingPageType() const { return LoadingPageType; }

	void SetCreateFrom(const ANSICHAR* File, const int32 Line);
	
	FDD_FadeEventDelegate OnFadeOutComplete;
	FDD_FadeEventDelegate OnFadeInStart;
	FDD_FadeEventDelegate OnFadeInComplete;

	FDD_FadeCheckLoadDelegate OnCheckLoadComplete;
	
private:
	EDD_FadeStyle Fade = EDD_FadeStyle::None;
	EDD_LoadingPageType LoadingPageType = EDD_LoadingPageType::None;
	bool bDirectFadeOut = false;
	
	FString CreateFileLine = FString();
};
