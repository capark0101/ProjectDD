// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_Button_DefaultImage.h"

#include "DD_Define.h"
#include "Style/DD_ButtonStyle_DefaultImage.h"

void UDD_Button_DefaultImage::SetNormalTexture(UTexture2D* Texture)
{
	UDD_ButtonStyle_DefaultImage* ImageButtonStyle = DD_NewObject<UDD_ButtonStyle_DefaultImage>();
	ImageButtonStyle->SetImage(Texture);
	SetStyle(ImageButtonStyle->StaticClass());
}
