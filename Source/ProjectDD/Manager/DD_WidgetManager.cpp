// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_WidgetManager.h"
#include "DD_BuiltInWidgetTool.h"
#include "DD_BasicUtilLibrary.h"
#include "DD_StateMachine.h"
#include "DD_Define.h"
#include "DD_Mapper_Resource_Widget.h"
#include "Resource_Widget.h"
#include "DD_TableManager.h"
#include "DD_Utility.h"
#include "DD_Widget.h"
#include "DD_WidgetDefine.h"

UDD_WidgetManager::UDD_WidgetManager()
{
}

UDD_WidgetManager::~UDD_WidgetManager()
{
}

void UDD_WidgetManager::BuiltInInitialize()
{
	TDD_Singleton<UDD_WidgetManager>::BuiltInInitialize();

	BuiltInTool = DD_NewObject<UDD_BuiltInWidgetTool>(this, TEXT("BuiltInWidgetTool"));
	if(IsValid(BuiltInTool.Get()) == false)
	{
		return;
	}

	BuiltInTool->BuiltInitialize();
}

void UDD_WidgetManager::Initialize()
{
	TDD_Singleton<UDD_WidgetManager>::Initialize();

	BuiltInTool->Initialize();
}

void UDD_WidgetManager::Finalize()
{
	TDD_Singleton<UDD_WidgetManager>::Finalize();

	ClearExclusiveLayer();
	ManagedWidgets.Empty();
}

void UDD_WidgetManager::BuiltInFinalize()
{
	TDD_Singleton<UDD_WidgetManager>::BuiltInFinalize();

	if(IsValid(BuiltInTool.Get()))
	{
		BuiltInTool->Finalize();
		DD_DeleteObject(BuiltInTool);
		BuiltInTool = nullptr;
	}
}

void UDD_WidgetManager::Tick(float DeltaTime)
{
	TDD_Singleton<UDD_WidgetManager>::Tick(DeltaTime);

	if(BuiltInTool)
	{
		BuiltInTool->Tick(DeltaTime);
	}
}

void UDD_WidgetManager::ClearExclusiveLayer()
{
	constexpr uint8 Top = static_cast<uint8>(EDD_ExclusiveGroup::TopMenu);
	constexpr uint8 Content = static_cast<uint8>(EDD_ExclusiveGroup::ContentMenu);

	if(ExclusiveLayers.IsValidIndex(Top))
	{
		ExclusiveLayers[Top] = nullptr;
	}
	if(ExclusiveLayers.IsValidIndex(Content))
	{
		ExclusiveLayers[Content] = nullptr;
	}
}

TObjectPtr<UDD_Widget> UDD_WidgetManager::DD_CreateWidget(const FName& TypeName)
{
	GEngine->ForceGarbageCollection(true);

	if(const TWeakObjectPtr<UDD_Widget>* pWidget = ManagedWidgets.Find(TypeName))
	{
		const TWeakObjectPtr<UDD_Widget>& PreviousWidget = *pWidget;
		if(PreviousWidget.IsValid())
		{
			return PreviousWidget.Get();
		}
		ManagedWidgets.Remove(TypeName);
	}

	const TObjectPtr<UDD_Widget> Widget = Cast<UDD_Widget>(CreateWidget_Internal(TypeName, true));
	DD_CHECK(Widget != nullptr);

	AddExclusiveLayerWidget(Widget);
	
	ManagedWidgets.Emplace(TypeName, Widget);

	if(OnCreateWidget.IsBound())
	{
		OnCreateWidget.Broadcast(TypeName);
	}
	
	return Widget;
}

TObjectPtr<UDD_Widget> UDD_WidgetManager::DD_CreateWidgetNotManaging(const FName& TypeName)
{
	GEngine->ForceGarbageCollection(true);

	const TObjectPtr<UDD_Widget> Widget = Cast<UDD_Widget>(CreateWidget_Internal(TypeName, true));
	DD_CHECK(Widget != nullptr);

	AddExclusiveLayerWidget(Widget);
	
	return Widget;
}

void UDD_WidgetManager::PreDestroyWidget(TObjectPtr<UDD_Widget> Widget)
{
	if(IsValid(Widget) == false)
	{
		return;
	}

	RemoveExclusiveLayerWidget(Widget);

	if(OnDestroyWidget.IsBound())
	{
		OnDestroyWidget.Broadcast(Widget->GetResourceWidgetInfo().GetWidgetName());
	}
}

bool UDD_WidgetManager::DestroyWidget(const FName& TypeName)
{
	TObjectPtr<UDD_Widget> Widget = GetWidget(TypeName);
	if(Widget == nullptr)
	{
		return false;
	}

	PreDestroyWidget(Widget);
	Widget->FinishWidget();

	ManagedWidgets.Remove(TypeName);
	Widget = nullptr;
	PostDestroyWidget(TypeName);	
	return true;
}

void UDD_WidgetManager::PostDestroyWidget(const FName& TypeName)
{
}

TObjectPtr<UDD_Widget> UDD_WidgetManager::GetWidget(const FName& TypeName)
{
	const TWeakObjectPtr<UDD_Widget>* pWidget = ManagedWidgets.Find(TypeName);
	if(pWidget && pWidget->IsValid())
	{
		return pWidget->Get();
	}

	return nullptr;
}

TObjectPtr<UDD_Widget> UDD_WidgetManager::CreateWidgetNotManaging(const FString& Path) const
{
	return CreateWidget_Internal_NotManaging(Path);
}

TObjectPtr<UDD_Widget> UDD_WidgetManager::CreateWidgetNotManagingBySOP(const FSoftObjectPath& SoftObjectPath) const
{
	const TObjectPtr<UDD_Widget> Widget = CreateWidgetNotManaging(SoftObjectPath.ToString());
	DD_CHECK(Widget != nullptr);
	
	return Widget;
}

TObjectPtr<UDD_Widget> UDD_WidgetManager::CreateWidget_Internal(const FName& TypeName, bool bManaged)
{
	const TObjectPtr<UDD_Mapper_Resource_Widget> ResourceWidgetMapper = Cast<UDD_Mapper_Resource_Widget>(gTableMng.GetTableMapper(EDD_TableDataType::Resource_Widget));
	if(ResourceWidgetMapper == nullptr)
	{
		return nullptr;
	}

	const FResource_Widget* ResourceWidgetData = ResourceWidgetMapper->GetResourceWidgetData(TypeName);
	if(ResourceWidgetData == nullptr)
	{
		// 테이블 자료 문제
		return nullptr;
	}

	const FString ResourcePath = gTableMng.GetPath(EDD_TableDataType::BasePath_BP_File, ResourceWidgetData->Path_File, true);

	const TObjectPtr<UDD_Widget> ResultWidget = bManaged ? CreateWidget_Internal_Managing(ResourcePath) : CreateWidget_Internal_NotManaging(ResourcePath);

	if(ResultWidget == nullptr)
	{
		return nullptr;
	}

	FDD_ResourceWidgetInfo WidgetInfo;
	WidgetInfo.TypeName = ResourceWidgetData->TypeName;
	WidgetInfo.File = ResourcePath;
	WidgetInfo.zOrder = ResourceWidgetData->zOrder;
	WidgetInfo.ExclusiveGroup = static_cast<EDD_ExclusiveGroup>(ResourceWidgetData->ExclusiveGroup);
	WidgetInfo.NotRender3D = ResourceWidgetData->NotRender3D;

	ResultWidget->SetZOrder(WidgetInfo.zOrder);
	ResultWidget->SetResourceWidgetInfo(WidgetInfo);
	ResultWidget->InitWidget(TypeName, bManaged);

	return ResultWidget;
}

TObjectPtr<UDD_Widget> UDD_WidgetManager::CreateWidget_Internal_Managing(const FString& Path)
{
	static FString SubName = TEXT("Create Widget");
	
	const TObjectPtr<UClass> WidgetClass = Cast<UClass>(DD_Utility::LoadObjectFromFile(Path, FDD_LoadResourceDelegate::CreateUObject(this, &UDD_WidgetManager::LoadComplete)));
	if(WidgetClass == nullptr)
	{
		return nullptr;
	}

	const TObjectPtr<UWorld> World = UDD_BasicUtilLibrary::GetGameWorld();
	if(World == nullptr)
	{
		return nullptr;
	}

	return CreateWidget<UDD_Widget>(World, WidgetClass);
}

TObjectPtr<UDD_Widget> UDD_WidgetManager::CreateWidget_Internal_NotManaging(const FString& Path) const
{
	static FString SubName = TEXT("Create Widget");
	const FString ClassName = Path + TEXT("_C");
	
	const TObjectPtr<UClass> WidgetClass = Cast<UClass>(DD_Utility::LoadObjectFromFile(ClassName));
	const TObjectPtr<UWorld> World = UDD_BasicUtilLibrary::GetGameWorld();
	
	if(World != nullptr && World->bIsTearingDown == false)
	{
		if(const TObjectPtr<UDD_Widget> Widget = CreateWidget<UDD_Widget>(World, WidgetClass))
		{
			Widget->Init();
			return Widget;
		}
	}
	
	return nullptr;
}

void UDD_WidgetManager::AddExclusiveLayerWidget(TObjectPtr<UDD_Widget> Widget)
{
	if(Widget == nullptr)
	{
		return;
	}

	const uint8 GroupIndex = static_cast<uint8>(Widget->GetResourceWidgetInfo().GetExclusiveGroup());
	if(GroupIndex != 0)
	{
		if(ExclusiveLayers.IsValidIndex(GroupIndex) && IsValid(ExclusiveLayers[GroupIndex]) && ExclusiveLayers[GroupIndex] != Widget)
		{
			const TObjectPtr<UDD_Widget> PreviousWidget = ExclusiveLayers[GroupIndex];
			if(IsValid(PreviousWidget))
			{
				DestroyWidget(PreviousWidget->GetResourceWidgetInfo().GetWidgetName());
			}
		}

		ExclusiveLayers[GroupIndex] = Widget;
	}
}

void UDD_WidgetManager::RemoveExclusiveLayerWidget(TObjectPtr<UDD_Widget> Widget)
{
	if(Widget == nullptr)
	{
		return;
	}

	const uint8 GroupIndex = static_cast<uint8>(Widget->GetResourceWidgetInfo().GetExclusiveGroup());

	if(GroupIndex != 0 && ExclusiveLayers.Num() > 0 && IsValid(ExclusiveLayers[GroupIndex]) && ExclusiveLayers[GroupIndex] != Widget)
	{
		ExclusiveLayers[GroupIndex] = nullptr;
	}
}

void UDD_WidgetManager::LoadComplete(const FString& TableName, TObjectPtr<UObject> WidgetData)
{
}

void UDD_WidgetManager::ProcessBuiltInCompass()
{
}
