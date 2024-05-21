// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DD_Widget.h"
#include "DD_Widget_LobbyTop.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UDD_Widget_LobbyTop : public UDD_Widget
{
	GENERATED_BODY()
	
public:
	virtual void InitWidget(const FName& TypeName, bool _bManaged, bool bActivate) override;
	virtual void FinishWidget() override;

	void SetTopData(const struct FDD_LobbyTopData& TopData) const;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UDD_Widget_Profile> CPP_ProfileWidget = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UDD_Widget_Resource> CPP_ResourceWidget_1 = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UDD_Widget_Resource> CPP_ResourceWidget_2 = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UDD_Widget_Resource> CPP_ResourceWidget_3 = nullptr;

	TArray<TObjectPtr<class UDD_Widget_Resource>> ResourceWidgets;
};
