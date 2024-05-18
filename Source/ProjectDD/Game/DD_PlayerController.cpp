// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_PlayerController.h"

#include "GameFramework/InputSettings.h"
#include "Input/DD_TouchInterface.h"
#include "Input/DD_VirtualJoyStick.h"
#include "Slate/DeferredCleanupSlateBrush.h"
#include "Utils/DD_Define.h"

ADD_PlayerController::ADD_PlayerController()
{
	SetShowMouseCursor(true);
}

ADD_PlayerController::~ADD_PlayerController()
{
}

void ADD_PlayerController::CreateTouchInterface()
{
	const TObjectPtr<ULocalPlayer> LocalPlayer = Cast<ULocalPlayer>(Player);

	if(IsValid(LocalPlayer) == false)
	{
		return;
	}

	if(IsValid(LocalPlayer->ViewportClient) && SDD_VirtualJoyStick::ShouldDisplayTouchInterface())
	{
		if(VirtualJoystick.IsValid())
		{
			Cast<ULocalPlayer>(Player)->ViewportClient->RemoveViewportWidgetContent(VirtualJoystick.ToSharedRef());
		}

		if(CurrentTouchInterface == nullptr)
		{
			const FSoftObjectPath& DefaultTouchInterfaceName = GetDefault<UInputSettings>()->DefaultTouchInterface;

			if(DefaultTouchInterfaceName.IsValid())
			{
				const FSoftClassPath& ClassPath = FSoftClassPath(*DefaultTouchInterfaceName.ToString());
				if(ClassPath.IsValid())
				{
					if(const TObjectPtr<UClass> TouchInterfaceClass = Cast<UClass>(ClassPath.TryLoad()))
					{
						CurrentTouchInterface = DD_NewObject<UDD_TouchInterface>(this, TouchInterfaceClass);
					}
				}
			}
		}

		if(CurrentTouchInterface)
		{
			// 조이스틱 생성
			VirtualJoystick = SNew(SDD_VirtualJoyStick);

			// 플레이어 뷰포트에 때려넣음
			LocalPlayer->ViewportClient->AddViewportWidgetContent(VirtualJoystick.ToSharedRef());

			ActivateTouchInterface(CurrentTouchInterface);
		}
	}
}

void ADD_PlayerController::ActivateTouchInterface(UTouchInterface* NewTouchInterface)
{
	if(NewTouchInterface)
	{
		if(VirtualJoystick.IsValid())
		{
			if(SDD_VirtualJoyStick* DD_VirtualJoyStick = static_cast<SDD_VirtualJoyStick*>(VirtualJoystick.Get()))
			{
				if(const TObjectPtr<UDD_TouchInterface> TouchInterface = Cast<UDD_TouchInterface>(NewTouchInterface))
				{
					DD_VirtualJoyStick->ImageCenter = TouchInterface->ImageCenter ? StaticCastSharedRef<ISlateBrushSource>(FDeferredCleanupSlateBrush::CreateBrush(TouchInterface->ImageCenter)) : TSharedPtr<ISlateBrushSource>();
					DD_VirtualJoyStick->CenterImageSize = TouchInterface->CenterImageSize;
					DD_VirtualJoyStick->CenterImageOpacity = TouchInterface->CenterImageOpacity;
					DD_VirtualJoyStick->ImageOuter = TouchInterface->ImageOuter ? StaticCastSharedRef<ISlateBrushSource>(FDeferredCleanupSlateBrush::CreateBrush(TouchInterface->ImageOuter)) : TSharedPtr<ISlateBrushSource>();
					DD_VirtualJoyStick->OuterImageSize = TouchInterface->OuterImageSize;
					DD_VirtualJoyStick->OuterImageOpacity = TouchInterface->OuterImageOpacity;
					DD_VirtualJoyStick->OuterImageSize = TouchInterface->OuterImageSize;
					DD_VirtualJoyStick->Center = TouchInterface->Controls[0].Center;
					DD_VirtualJoyStick->ThumbSize = TouchInterface->Controls[0].ThumbSize;
					DD_VirtualJoyStick->InteractionSize = TouchInterface->Controls[0].InteractionSize;
					DD_VirtualJoyStick->InputScale = TouchInterface->Controls[0].InputScale;
				}
			}
		}
	}
	
	Super::ActivateTouchInterface(NewTouchInterface);
}

SDD_VirtualJoyStick* ADD_PlayerController::GetVirtualJoyStick() const
{
	if(SVirtualJoystick* JoyStick = VirtualJoystick.Get())
	{
		return static_cast<SDD_VirtualJoyStick*>(JoyStick);
	}
	
	return nullptr;
}
