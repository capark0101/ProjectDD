// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_ButtonStyle_DefaultImage.h"

void UDD_ButtonStyle_DefaultImage::SetImage(UTexture2D* Texture)
{
	NormalBase.SetResourceObject(Texture);
}
