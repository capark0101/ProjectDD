// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_Button_DefaultText.h"
#include "CommonTextBlock.h"

void UDD_Button_DefaultText::SetNormalText(const FString& Text) const
{
	CPP_ButtonText->SetText(FText::FromString(Text));
}
