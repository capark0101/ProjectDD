// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DD_Singleton.h"
#include "UObject/Object.h"
#include "DD_WidgetDefine.h"
#include "DD_WidgetManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UDD_WidgetManager : public UObject, public TDD_Singleton<UDD_WidgetManager>
{
	GENERATED_BODY()
	
public:
	UDD_WidgetManager();
	virtual ~UDD_WidgetManager() override;

	virtual void BuiltInInitialize() override;
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void BuiltInFinalize() override;
	virtual void Tick(float DeltaTime) override;

	void ClearExclusiveLayer();

	TObjectPtr<class UDD_Widget> DD_CreateWidget(const FName& TypeName);
	TObjectPtr<class UDD_Widget> DD_CreateWidgetNotManaging(const FName& TypeName);
	
	void PreDestroyWidget(TObjectPtr<class UDD_Widget> Widget);
	bool DestroyWidget(const FName& TypeName);
	void PostDestroyWidget(const FName& TypeName);
	TObjectPtr<class UDD_Widget> GetWidget(const FName& TypeName);
	TObjectPtr<class UDD_Widget> CreateWidgetNotManaging(const FString& Path) const;
	TObjectPtr<class UDD_Widget> CreateWidgetNotManagingBySOP(const FSoftObjectPath& SoftObjectPath) const;
	
	TObjectPtr<class UDD_BuiltInWidgetTool> GetBuiltInWidgetTool() const { return BuiltInTool; }

	FDD_CreateWidget OnCreateWidget;
	FDD_DestroyWidget OnDestroyWidget;

private:
	TObjectPtr<class UDD_Widget> CreateWidget_Internal(const FName& TypeName, bool bManaged);
	TObjectPtr<class UDD_Widget> CreateWidget_Internal_Managing(const FString& Path);
	TObjectPtr<class UDD_Widget> CreateWidget_Internal_NotManaging(const FString& Path) const;
	
	void AddExclusiveLayerWidget(TObjectPtr<class UDD_Widget> Widget);
	void RemoveExclusiveLayerWidget(TObjectPtr<class UDD_Widget> Widget);

	void LoadComplete(const FString& TableName, TObjectPtr<UObject> WidgetData);

	void ProcessBuiltInCompass();
	
	UPROPERTY()
	TObjectPtr<class UDD_BuiltInWidgetTool> BuiltInTool = nullptr;
	
	UPROPERTY()
	TArray<TObjectPtr<class UDD_Widget>> ExclusiveLayers;

	UPROPERTY()
	TMap<FName, TWeakObjectPtr<class UDD_Widget>> ManagedWidgets;
	
#define gWidgetMng (*UDD_WidgetManager::GetInstance())
};