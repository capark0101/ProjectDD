// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DD_TableDefine.h"
#include "Manager/DD_TableManager.h"
#include "Utils/DD_Define.h"

#include "DD_TableMapper.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UDD_TableMapper : public UObject
{
	GENERATED_BODY()

public:
	virtual void Initialize(TObjectPtr<class UDD_TableManager> Mng) {}
	virtual void Finalize() {}

	template<typename T>
	static void BuildTable(TObjectPtr<UDD_TableManager> TableManager, EDD_TableDataType Type, TMap<int32, T*>& MapperTable)
	{
		TMap<FName, uint8*> RowData;
		TableManager->GetRowDataMap(Type, RowData);

		MapperTable.Reset();
		for (auto& Pair : RowData)
		{
			// 열 데이터의 id 값 산출
			int32 Id = FCString::Atoi(*Pair.Key.ToString());
			// 해당 구조체를 명시하여 캐스팅(구조체가 다르면 안되니까 무조건 강제 고정 캐스팅)
			T* Data = reinterpret_cast<T*>(Pair.Value);
			if (Id > 0 && Data)
			{
				MapperTable.Emplace(Id, Data);
			}
			else
			{
				DD_LOG(TEXT("Table Id or Data is Wrong!!!!!!. PleaseCheck ExcelTable or TableType"));
			}
		}
	}

private:
};
