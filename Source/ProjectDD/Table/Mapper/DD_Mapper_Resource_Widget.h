// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Table/DD_TableMapper.h"
#include "DD_Mapper_Resource_Widget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UDD_Mapper_Resource_Widget : public UDD_TableMapper
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(TObjectPtr<UDD_TableManager> Mng) override;
	virtual void Finalize() override;
	
	struct FResource_Widget* GetResourceWidgetData(const FName& TypeName);
	
private:
	TMap<FName, FResource_Widget*> ResourceWidgetDatas;
};
