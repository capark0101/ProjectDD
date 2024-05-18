// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_InputManager.h"

#include "Actor/Pawn/DD_Input.h"
#include "Utils/DD_Utility.h"

void UDD_InputManager::Initialize()
{
	TDD_Singleton<UDD_InputManager>::Initialize();
}

void UDD_InputManager::Finalize()
{
	TDD_Singleton<UDD_InputManager>::Finalize();
}

void UDD_InputManager::Tick(float _DeltaTime)
{
	TDD_Singleton<UDD_InputManager>::Tick(_DeltaTime);
}

void UDD_InputManager::RegistAxis(EDD_Axis_Type AxisType, EDD_Action_Type ActionType, const FInputAxisUnifiedDelegate& Event)
{
	if(AxisType == EDD_Axis_Type::Left)
	{
		if(ActionType == EDD_Action_Type::ActionUpDown)
		{
			CharacterMove_UpDownEvent.AxisDelegate = Event;
		}
		else if(ActionType == EDD_Action_Type::ActionLeftRight)
		{
			CharacterMove_LeftRightEvent.AxisDelegate = Event;
		}	
	}
	else if(AxisType == EDD_Axis_Type::Right)
	{
		if(ActionType == EDD_Action_Type::ActionUpDown)
		{
			CameraMove_UpDownEvent.AxisDelegate = Event;
		}
		else if(ActionType == EDD_Action_Type::ActionLeftRight)
		{
			CameraMove_LeftRightEvent.AxisDelegate = Event;
		}
	}
}

void UDD_InputManager::RegistTouch(EDD_Touch_Event TouchEventType, const FInputTouchBinding& Event)
{
	if(TouchEventType == EDD_Touch_Event::Down)
	{
		TouchDownEvent = Event;
	}
	else if(TouchEventType == EDD_Touch_Event::Up)
	{
		TouchUpEvent = Event;
	}
	else if(TouchEventType == EDD_Touch_Event::Move)
	{
		TouchMoveEvent = Event;
	}
}

void UDD_InputManager::RegistAndroidButton(EDD_AndroidButton_Type ButtonType, const FSimpleDelegate& Delegate)
{
	if(ButtonType == EDD_AndroidButton_Type::Back)
	{
		AndroidBackDelegate = Delegate;
	}
	else if(ButtonType == EDD_AndroidButton_Type::Menu)
	{
		AndroidMenuDelegate = Delegate;
	}
}

void UDD_InputManager::CreateInputPawn()
{
	if(InputPawn != nullptr)
	{
		return;
	}

	InputPawn = Cast<ADD_Input>(DD_Utility::SpawnActor(ADD_Input::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, TEXT("InputPawn"), ESpawnActorCollisionHandlingMethod::AlwaysSpawn, true));
	if(InputPawn)
	{
		InputPawn->Create();
	}
}

void UDD_InputManager::DestroyInputPawn()
{
	if(InputPawn != nullptr)
	{
		InputPawn->Destroy();

		if(InputPawn->IsRooted())
		{
			InputPawn->RemoveFromRoot();
		}

		UDD_BasicUtilLibrary::GetGameWorld()->DestroyActor(InputPawn);
		
		InputPawn = nullptr;
	}
}

void UDD_InputManager::LeftAxisUpDown(float Value)
{
	CharacterMove_UpDownEvent.AxisDelegate.Execute(Value);
}

void UDD_InputManager::LeftAxisLeftRight(float Value)
{
	CharacterMove_LeftRightEvent.AxisDelegate.Execute(Value);
}

void UDD_InputManager::RightAxisUpDown(float Value)
{
	CameraMove_UpDownEvent.AxisDelegate.Execute(Value);
}

void UDD_InputManager::RightAxisLeftRight(float Value)
{
	CameraMove_LeftRightEvent.AxisDelegate.Execute(Value);
}

void UDD_InputManager::OnTouchDown(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	TouchDownEvent.TouchDelegate.Execute(FingerIndex, Location);
}

void UDD_InputManager::OnTouchUp(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	TouchUpEvent.TouchDelegate.Execute(FingerIndex, Location);
}

void UDD_InputManager::OnTouchMove(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	TouchMoveEvent.TouchDelegate.Execute(FingerIndex, Location);
}

void UDD_InputManager::AndroidBack()
{
	if(AndroidBackDelegate.IsBound())
	{
		AndroidBackDelegate.Execute();
	}
}

void UDD_InputManager::AndroidMenu()
{
	if(AndroidMenuDelegate.IsBound())
	{
		AndroidMenuDelegate.Execute();
	}
}
