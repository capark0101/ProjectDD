// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_Button.h"

#include "DD_BasicUtilLibrary.h"

UDD_Button::UDD_Button()
{
}

UDD_Button::~UDD_Button()
{
}

void UDD_Button::NativeConstruct()
{
	Super::NativeConstruct();
}

void UDD_Button::NativeOnCurrentTextStyleChanged()
{
	Super::NativeOnCurrentTextStyleChanged();
}

const FText UDD_Button::GetPaletteCategory()
{
	return FText::FromString("DD Custom");
}

void UDD_Button::SetDelegates()
{
	OnClicked().AddUObject(this, &UDD_Button::OnClick);
	OnPressed().AddUObject(this, &UDD_Button::OnPress);
	OnReleased().AddUObject(this, &UDD_Button::OnRelease);
	OnHovered().AddUObject(this, &UDD_Button::OnHover);
	OnUnhovered().AddUObject(this, &UDD_Button::OnUnhover);
}

void UDD_Button::OnClick()
{
	if (IsUseClockedDelay())
	{
		const TObjectPtr<UWorld> World = UDD_BasicUtilLibrary::GetGameWorld();
		if (!World)
		{
			DD_CHECK(false);
			DD_LOG(TEXT("Wrong Process Please Check CY_Button Class"))
				return;
		}

		const float CurrentClickedTime = GetWorld() == nullptr ? 0.f : GetWorld()->GetUnpausedTimeSeconds();
		if (LastClickedTime + ClickedDelayTime >= CurrentClickedTime)
		{
			DD_OnClickedInDelayTimeDelegate.Broadcast();
			return;
		}
		LastClickedTime = GetWorld() == nullptr ? 0.f : GetWorld()->GetUnpausedTimeSeconds();
	}

	if (IsUseLongPressedEvent() == false)
	{
		DD_OnClickedDelegate.Broadcast();
	}
}

void UDD_Button::OnPress()
{
	if(IsUseLongPressedEvent())
	{
		FTimerManager& TimerManager = UDD_BasicUtilLibrary::GetGameWorld()->GetTimerManager();
		TimerManager.SetTimer(PressTimerHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			DD_OnLongPressedDelegate.Broadcast();
		}), LongPressedTime, false);
	}
	DD_OnPressedDelegate.Broadcast();
}

void UDD_Button::OnRelease()
{
	DD_OnReleasedDelegate.Broadcast();

	if(IsUseLongPressedEvent())
	{
		FTimerManager& TimerManager = UDD_BasicUtilLibrary::GetGameWorld()->GetTimerManager();
		if(TimerManager.IsTimerActive(PressTimerHandle))
		{
			TimerManager.ClearTimer(PressTimerHandle);
		}
	}
}

void UDD_Button::OnHover()
{
	DD_OnHoveredDelegate.Broadcast();
}

void UDD_Button::OnUnhover()
{
	DD_OnUnhoveredDelegate.Broadcast();
}
