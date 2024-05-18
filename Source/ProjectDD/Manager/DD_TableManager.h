// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DD_Singleton.h"
#include "Engine/DataTable.h"
#include "Table/DD_TableDefine.h"

#include "DD_TableManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UDD_TableManager : public UObject, public TDD_Singleton<UDD_TableManager>
{
	GENERATED_BODY()
public:
	UDD_TableManager();
	~UDD_TableManager();

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Tick(float DeltaTime) override;

	virtual void GetRowDataMap(EDD_TableDataType TableType, TMap<FName, uint8*>& OutMapper);

	FDD_TableMapperData* GetTableMapperData(EDD_TableDataType TableType);
	FString GetPath(EDD_TableDataType TableType, int32 Key, bool bResourcePath = false);
	FString GetDirectory(int32 DirectoryTableId);
	
	TObjectPtr<UDataTable> GetTableData(EDD_TableDataType TableType);

	
	TObjectPtr<UDD_TableMapper> GetTableMapper(EDD_TableDataType TableType);
	
	template<typename FRowData>
	FRowData* GetTableRowData(EDD_TableDataType TableType, int32 Key)
	{
		const FDD_TableMapperData* TableMapper = GetTableMapperData(TableType);
		if (TableMapper == nullptr)  
		{
			return nullptr;
		}

		const TObjectPtr<UDataTable> TableData = TableMapper->GetTableData();
		const FName KeyName = FName(FString::FromInt(Key));
		const FString Context = TEXT("GENERAL");
		return TableData->FindRow<FRowData>(KeyName, Context);
	}

	int32 GetTableRowNum(EDD_TableDataType TableType)
	{
		const FDD_TableMapperData* TableMapper = GetTableMapperData(TableType);
		if (TableMapper == nullptr)
		{
			return 0;
		}

		if(const TObjectPtr<UDataTable> TableData = TableMapper->GetTableData())
		{
			return TableData->GetRowMap().Num();
		}
		return 0;
	}

private:
	void ResetData();
	void CreateTableData(EDD_TableDataType TableType, const FString& Path, TSubclassOf<UDD_TableMapper> MapperType = nullptr);
	void MakeTableStructData();

	void LoadComplete(const FString& TableName, TObjectPtr<UObject> TableData);
	
	UPROPERTY()
	TMap<EDD_TableDataType, FDD_TableMapperData> TableMappers;

	bool bInitialize = false;

#define gTableMng (*UDD_TableManager::GetInstance())
};
