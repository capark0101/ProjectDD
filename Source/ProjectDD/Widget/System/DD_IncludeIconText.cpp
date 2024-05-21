// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_IncludeIconText.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UDD_IncludeIconText::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if(IconImage)
	{
		CPP_Icon->SetBrushFromTexture(IconImage);
	}

	if(Text.Len() > 0)
	{
		CPP_Text->SetText(FText::FromString(Text));
	}
}
