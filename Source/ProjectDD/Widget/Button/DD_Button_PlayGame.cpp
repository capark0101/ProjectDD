// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_Button_PlayGame.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UDD_Button_PlayGame::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	
	if(Text.Len() > 0)
	{
		CPP_TitleText->SetText(FText::FromString(Text));
	}
	
	if(IconImage)
	{
		CPP_Icon->SetBrushFromTexture(IconImage);
	}
}
