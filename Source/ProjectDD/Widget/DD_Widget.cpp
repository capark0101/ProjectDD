// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_Widget.h"

#include "DD_WidgetDefine.h"
#include "MovieScene.h"
#include "Animation/WidgetAnimation.h"
#include "Blueprint/WidgetTree.h"
#include "Button/DD_Button.h"

void UDD_Widget::NativeConstruct()
{
	Super::NativeConstruct();
	MakeButtonPool();
}

void UDD_Widget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UDD_Widget::InitWidget(const FName& TypeName, bool _bManaged, bool bActivate)
{
	bManaged = _bManaged;

	FillDefaultAnimations();
	
	if(bActivate)
	{
		Active(true);
	}

	SetOriginVisible(GetVisibility());

	InitResourceWidgetInfo();
}

void UDD_Widget::FinishWidget()
{
	if(IsValid(this) == false || this->IsValidLowLevel() == false)
	{
		return;
	}

	StopAllAnimations();
	DeActive();
}

void UDD_Widget::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UDD_Widget::CloseWidget()
{
	if(bManaged)
	{
		//gWidgetMng.DestroyWidget(GetResourceWidgetInfo().GetWidgetName());
	}
}

void UDD_Widget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UDD_Widget::DeActive(bool bImmediately)
{
	if(bImmediately == false)
	{
		SetVisibility(ESlateVisibility::HitTestInvisible);
	}

	if(IsExistAnim(DefaultWidgetAnimation::DisAppearance) && bImmediately == false)
	{
		PlayAnimationByName(DefaultWidgetAnimation::DisAppearance);
	}
	else
	{
		RemoveFromParent();
	}
	bActive = false;
}

void UDD_Widget::Active(bool _bActive)
{
	if(bAddToViewport == false)
	{
		AddToViewport(_bActive ? ZOrder : 0);
	}
	
	if(IsVisible())
	{
		if(IsExistAnim(DefaultWidgetAnimation::Appearance) == true)
		{
			PlayAnimationByName(DefaultWidgetAnimation::Appearance);
		}

		if(_bActive == false)
		{
			SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	bActive = _bActive;
}

void UDD_Widget::OnAnimationStarted_Implementation(const UWidgetAnimation* Animation)
{
	Super::OnAnimationStarted_Implementation(Animation);
}

void UDD_Widget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	Super::OnAnimationFinished_Implementation(Animation);

	OnAnimFinished(FName(Animation->GetMovieScene()->GetName()));
}

void UDD_Widget::Init()
{
	bActive = false;
	bAddToViewport = false;
}

void UDD_Widget::FillDefaultAnimations()
{
	Animations.Empty();

	FProperty* Property = GetClass()->PropertyLink;
	while(Property != nullptr)
	{
		if(Property->GetClass() == FObjectProperty::StaticClass())
		{
			if(const FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property))
			{
				if(ObjectProperty->PropertyClass == UWidgetAnimation::StaticClass())
				{
					TObjectPtr<UWidgetAnimation> WidgetAnimObject = Cast<UWidgetAnimation>(ObjectProperty->GetObjectPropertyValue_InContainer(this));

					if(WidgetAnimObject && WidgetAnimObject->MovieScene != nullptr)
					{
						Animations.Emplace(WidgetAnimObject->GetMovieScene()->GetName(), WidgetAnimObject);
					}
				}
			}
		}
		Property = Property->PropertyLinkNext;
	}
}

void UDD_Widget::MakeButtonPool()
{
	if (const TObjectPtr<UWidgetTree> WidgetTreePtr = WidgetTree.Get())
	{
		WidgetTreePtr->ForEachWidget([&](UWidget* Widget)
			{
				check(Widget);

				if (Widget->IsA(UDD_Button::StaticClass()))
				{
					if (const TObjectPtr<UDD_Button> Button = Cast<UDD_Button>(Widget))
					{
						Buttons.Emplace(Button);
					}
				}
			});
	}
}

void UDD_Widget::PlayAnimationByName(FName Name, float StartTime, int32 LoopCount, EUMGSequencePlayMode::Type PlayType,	float Speed)
{
	if(const TObjectPtr<UWidgetAnimation> WidgetAnimation = GetAnimationByName(Name))
	{
		PlayAnimation(WidgetAnimation, StartTime, LoopCount, PlayType, Speed);
	}
}

TObjectPtr<UWidgetAnimation> UDD_Widget::GetAnimationByName(FName AnimName) const
{
	TObjectPtr<UWidgetAnimation> const* pWidgetAnim = Animations.Find(AnimName);

	return pWidgetAnim == nullptr ? nullptr : *pWidgetAnim;
}

bool UDD_Widget::StopAnimation(const FName& AnimName)
{
	if(const TObjectPtr<UWidgetAnimation> WidgetAnimation = GetAnimationByName(AnimName))
	{
		UUserWidget::StopAnimation(WidgetAnimation);
		return true;
	}

	return false;
}

void UDD_Widget::SetOriginVisible(ESlateVisibility _Visibility)
{
	OriginVisibility = _Visibility;
}

void UDD_Widget::OnAnimFinished(const FName& AnimName)
{
	if(AnimName == DefaultWidgetAnimation::Appearance)
	{
		PlayIdleAnimation();
	}
}

void UDD_Widget::InitResourceWidgetInfo()
{
	if(bManaged == false)
	{
		return;
	}
}

void UDD_Widget::PlayIdleAnimation()
{
	if(GetAnimationByName(DefaultWidgetAnimation::Idle))
	{
		PlayAnimationByName(DefaultWidgetAnimation::Idle, 0.f, 0);
	}
}

bool UDD_Widget::IsExistAnim(FName AnimName) const
{
	const TObjectPtr<UWidgetAnimation> WidgetAnim = GetAnimationByName(AnimName);

	return WidgetAnim != nullptr;
}
