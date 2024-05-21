// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DD_WidgetDefine.h"
#include "Blueprint/UserWidget.h"
#include "DD_Widget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UDD_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void InitWidget(const FName& TypeName, bool _bManaged, bool bActivate = true);
	virtual void FinishWidget();

	virtual void SynchronizeProperties() override;
	
	UFUNCTION()
	virtual void CloseWidget();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void DeActive(bool bImmediately = false);
	virtual void Active(bool _bActive = true);

	virtual void OnAnimationStarted_Implementation(const UWidgetAnimation* Animation) override;
	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;
	
	void Init();

	void FillDefaultAnimations();
	void MakeButtonPool();

	void PlayAnimationByName(FName Name, float StartTime = 0.f, int32 LoopCount = 1, EUMGSequencePlayMode::Type PlayType = EUMGSequencePlayMode::Forward, float Speed = 1.f);
	TObjectPtr<UWidgetAnimation> GetAnimationByName(FName AnimName) const;
	bool StopAnimation(const FName& AnimName);
	
	FORCEINLINE void SetResourceWidgetInfo(const FDD_ResourceWidgetInfo& Info) { ResourceWidgetInfo = Info; }
	FORCEINLINE FDD_ResourceWidgetInfo GetResourceWidgetInfo() const { return ResourceWidgetInfo; }
	FORCEINLINE void SetZOrder(int32 _ZOrder) { ZOrder = _ZOrder; }

	UFUNCTION(BlueprintCallable, Category = "UCY_Widget")
	void SetOriginVisible(ESlateVisibility _Visibility);
protected:
	virtual void OnAnimFinished(const FName& AnimName);
	
	void InitResourceWidgetInfo();

	void PlayIdleAnimation();
	
	bool bActive;
	bool bAddToViewport;
	bool bManaged = true;

	ESlateVisibility OriginVisibility;
	
	UPROPERTY(Category = UCY_Widget, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 ZOrder = 0;

	FDD_ResourceWidgetInfo ResourceWidgetInfo;

	UPROPERTY()
	TMap<FName, TObjectPtr<UWidgetAnimation>> Animations;
	
private:
	bool IsExistAnim(FName AnimName) const;
	
	UPROPERTY()
	TArray<class UDD_Button*> Buttons;
};
