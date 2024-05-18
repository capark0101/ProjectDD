// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_Input.h"

#include "Manager/DD_InputManager.h"


// Sets default values
ADD_Input::ADD_Input()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADD_Input::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADD_Input::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADD_Input::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if(NewInputComponent != PlayerInputComponent)
	{
		NewInputComponent = PlayerInputComponent;
		if(NewInputComponent == nullptr)
		{
			return;
		}
	}
	UDD_InputManager* InputManager = gInputMng.GetInstance();
	NewInputComponent->BindAxis("LEFT_AXIS_UPDOWN", InputManager, &UDD_InputManager::LeftAxisUpDown);
	NewInputComponent->BindAxis("LEFT_AXIS_LEFTRIGHT", InputManager, &UDD_InputManager::LeftAxisLeftRight);
	NewInputComponent->BindAxis("RIGHT_AXIS_UPDOWN", InputManager, &UDD_InputManager::RightAxisUpDown);
	NewInputComponent->BindAxis("RIGHT_AXIS_LEFTRIGHT", InputManager, &UDD_InputManager::RightAxisLeftRight);

	NewInputComponent->BindTouch(IE_Pressed, InputManager, &UDD_InputManager::OnTouchDown);
	NewInputComponent->BindTouch(IE_Released, InputManager, &UDD_InputManager::OnTouchUp);
	NewInputComponent->BindTouch(IE_Repeat, InputManager, &UDD_InputManager::OnTouchMove);

	NewInputComponent->BindAction("AndroidBack", IE_Pressed, InputManager, &UDD_InputManager::AndroidBack);
	NewInputComponent->BindAction("AndroidMenu", IE_Pressed, InputManager, &UDD_InputManager::AndroidMenu);
}

bool ADD_Input::Create()
{
	if (NewInputComponent == nullptr) 
		return false;
	
	const FKey _Key = EKeys::AnyKey;

	// pressed
	FInputKeyBinding KeyBindPressed(FInputChord(_Key, false, false, false, false), EInputEvent::IE_Pressed);
	KeyBindPressed.bConsumeInput = true;
	KeyBindPressed.bExecuteWhenPaused = false;
	KeyBindPressed.KeyDelegate.GetDelegateWithKeyForManualSet().BindWeakLambda(this, [=](const FKey& Key)
	{
		gInputMng.GetBindAllKeysDelegate().ExecuteIfBound(Key, true);
	});
	NewInputComponent->KeyBindings.Add(KeyBindPressed);

	// released
	FInputKeyBinding KeyBindReleased(FInputChord(_Key, false, false, false, false), EInputEvent::IE_Released);
	KeyBindReleased.bConsumeInput = true;
	KeyBindReleased.bExecuteWhenPaused = false;
	KeyBindReleased.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([=](const FKey& Key)
	{
		gInputMng.GetBindAllKeysDelegate().ExecuteIfBound(Key, false);
	});
	
	NewInputComponent->KeyBindings.Add(KeyBindReleased);
	bIsCreated = true;
	return true;
}

void ADD_Input::Destroy()
{
	bIsCreated = false;
	NewInputComponent = nullptr;
}

