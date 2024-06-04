// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_Mapper_Resource_Widget.h"
#include "Resource_Widget.h"

void UDD_Mapper_Resource_Widget::Initialize(TObjectPtr<UDD_TableManager> Mng)
{
	Super::Initialize(Mng);

	TMap<int32, FResource_Widget*> PrimitiveResourceWidget;
	PrimitiveResourceWidget.Empty();
	
	BuildTable(Mng, EDD_TableDataType::Resource_Widget, PrimitiveResourceWidget);

	for(const auto& ResourceWidgetData : PrimitiveResourceWidget)
	{
		ResourceWidgetDatas.Emplace(ResourceWidgetData.Value->TypeName, ResourceWidgetData.Value);
	}
}

void UDD_Mapper_Resource_Widget::Finalize()
{
	ResourceWidgetDatas.Empty();

	Super::Finalize();
}

FResource_Widget* UDD_Mapper_Resource_Widget::GetResourceWidgetData(const FName& TypeName)
{
	if(FResource_Widget** pResourceWidgetData = ResourceWidgetDatas.Find(TypeName))
	{
		return *pResourceWidgetData;
	}

	return nullptr;
}
