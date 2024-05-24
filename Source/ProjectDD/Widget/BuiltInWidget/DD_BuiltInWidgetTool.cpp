// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_BuiltInWidgetTool.h"
#include "DD_WidgetManager.h"
#include "DD_Widget_DialogScreenFader.h"

void UDD_BuiltInWidgetTool::BuiltInitialize()
{
	DialogScreenFader = Cast<UDD_Widget_DialogScreenFader>(gWidgetMng.CreateWidgetNotManagingBySOP(UDD_Widget_DialogScreenFader::GetWidgetPath()));
	if(DialogScreenFader)
	{
		DialogScreenFader->FillDefaultAnimations();
		DialogScreenFader->AddToViewport(500);
		DialogScreenFader->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UDD_BuiltInWidgetTool::Initialize()
{
}

void UDD_BuiltInWidgetTool::Finalize()
{
}

void UDD_BuiltInWidgetTool::Tick(float DeltaTime)
{
}
