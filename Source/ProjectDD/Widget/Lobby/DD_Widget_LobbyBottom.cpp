// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_Widget_LobbyBottom.h"

#include "DD_Define.h"
#include "DD_Widget_Lobby.h"
#include "Button/DD_Button_DefaultImage.h"
#include "Components/ScrollBox.h"
#include "Components/ScrollBoxSlot.h"

void UDD_Widget_LobbyBottom::SetScrollBox(TArray<FDD_LobbyBottomData> ButtonData) const
{
	CPP_ButtonScrollBox->ClearChildren();
	CPP_ButtonScrollBox->AddChild(DD_NewObject<UScrollBox>());
	
	for(int32 i = 0 ; i < ButtonData.Num() ; i++)
	{
		if(ButtonData.IsValidIndex(i))
		{
			const TObjectPtr<UDD_Button_DefaultImage> BottomButton = DD_NewObject<UDD_Button_DefaultImage>();
			BottomButton->SetNormalTexture(ButtonData[i].ButtonImage);
			BottomButton->SetOnClickedDelegate(ButtonData[i].ButtonEvent);
			CPP_ButtonScrollBox->AddChild(BottomButton);

			CPP_ButtonScrollBox->AddChild(DD_NewObject<UScrollBox>());
		}
	}

	for(const auto& Child : CPP_ButtonScrollBox->GetAllChildren())
	{
		if(const TObjectPtr<UScrollBoxSlot> ChildSlot = Cast<UScrollBoxSlot>(Child->Slot))
		{
			ChildSlot->SetSize(FSlateChildSize());
		}
	}
}
