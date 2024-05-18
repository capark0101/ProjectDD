// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_TableManager.h"

#include "Table/BasePath_BP_File.h"
#include "Table/BasePath_Directory.h"
#include "Table/BasePath_Img_File.h"
#include "Table/Mapper/DD_Mapper_Common.h"
#include "Table/Mapper/DD_Mapper_Enemy.h"
#include "Table/Mapper/DD_Mapper_PlayerStatus.h"
#include "Table/Mapper/DD_Mapper_Resource_Widget.h"
#include "Utils/DD_Utility.h"

UDD_TableManager::UDD_TableManager()
{
}

UDD_TableManager::~UDD_TableManager()
{
}

void UDD_TableManager::Initialize()
{
	if(bInitialize)
	{
		return;
	}
	MakeTableStructData();

	bInitialize = true;
}

void UDD_TableManager::Finalize()
{
	for (auto& TableMapper : TableMappers)
	{
		TableMapper.Value.Finalize();
	}

	TableMappers.Empty();
}

void UDD_TableManager::Tick(float DeltaTime)
{
	TDD_Singleton<UDD_TableManager>::Tick(DeltaTime);
}

void UDD_TableManager::GetRowDataMap(EDD_TableDataType TableType, TMap<FName, uint8*>& OutMapper)
{
	const FString& Name = DD_Utility::ConvertEnumToString<EDD_TableDataType>("ECY_TableDataType", TableType);

	const FDD_TableMapperData* TableMapper = TableMappers.Find(TableType);
	if (TableMapper == nullptr)
	{
		return;
	}

	const TObjectPtr<UDataTable> TableData = TableMapper->GetTableData();
	if (TableData == nullptr)
	{
		return;
	}

	OutMapper = TableData->GetRowMap();
}

FDD_TableMapperData* UDD_TableManager::GetTableMapperData(EDD_TableDataType TableType)
{
	FDD_TableMapperData* TableMapper = TableMappers.Find(TableType);
	if (TableMapper == nullptr)
	{
		const FString& TableName = DD_Utility::ConvertEnumToString<EDD_TableDataType>("ECY_TableDataType", TableType);
		DD_LOG(TEXT("Wrong Table Type. Please Check (%s) Table Type"), *TableName);
		return nullptr;
	}

	return TableMapper;
}

FString UDD_TableManager::GetPath(EDD_TableDataType TableType, int32 Key, bool bResourcePath)
{
	switch(TableType)
	{
	case EDD_TableDataType::BasePath_BP_File:
		{
			const FBasePath_BP_File* RowData = GetTableRowData<FBasePath_BP_File>(TableType, Key);
			
			// 테이블로 관리하는 경우 : 경로 + 파일 이름
			return bResourcePath ? GetDirectory(RowData->Directory_Table_Id) + RowData->BP_File_Name.ToString() + '.' + RowData->BP_File_Name.ToString() + TEXT("_C")
			// 관리 안하는 경우 : 레퍼런스 경로
				: FString::Format(TEXT("{0}{1}.{1}"), {GetDirectory(RowData->Directory_Table_Id), RowData->BP_File_Name.ToString()});
		}
		break;
	case EDD_TableDataType::BasePath_Img_File:
		{
			const FBasePath_Img_File* RowData = GetTableRowData<FBasePath_Img_File>(TableType, Key);

			// 테이블로 관리하는 경우 : 경로 + 파일 이름
			return bResourcePath ? GetDirectory(RowData->Directory_Table_Id) + RowData->Img_File_Name + '.' + RowData->Img_File_Name + TEXT("_C")
			// 관리 안하는 경우 : 레퍼런스 경로
				: FString::Format(TEXT("{0}{1}.{1}"), {GetDirectory(RowData->Directory_Table_Id), RowData->Img_File_Name});
		}
		break;
	default:
		return FString();
	}

	return FString();
}

FString UDD_TableManager::GetDirectory(int32 DirectoryTableId)
{
	if(DirectoryTableId == 0 || DirectoryTableId == INDEX_NONE)
	{
		return FString();
	}

	const FBasePath_Directory* RowData = GetTableRowData<FBasePath_Directory>(EDD_TableDataType::BasePath_Directory, DirectoryTableId);
	if(RowData == nullptr)
	{
		return FString();
	}

	FString ResultDirectory = RowData->Directory.StartsWith(TEXT("/Game/")) ? RowData->Directory : TEXT("/Game/") + RowData->Directory;

	return ResultDirectory[ResultDirectory.Len() - 1] != '/' ? ResultDirectory + "/" : ResultDirectory;
}

TObjectPtr<UDataTable> UDD_TableManager::GetTableData(EDD_TableDataType TableType)
{
	const FDD_TableMapperData* TableMapper = GetTableMapperData(TableType);
	if (TableMapper == nullptr)
	{
		return nullptr;
	}

	return TableMapper->GetTableData();
}

TObjectPtr<UDD_TableMapper> UDD_TableManager::GetTableMapper(EDD_TableDataType TableType)
{
	const FDD_TableMapperData* TableMapper = GetTableMapperData(TableType);
	if (TableMapper == nullptr)
	{
		return nullptr;
	}

	return TableMapper->GetTableMapper();
}

void UDD_TableManager::ResetData()
{
	TableMappers.Empty();
}

void UDD_TableManager::CreateTableData(EDD_TableDataType TableType, const FString& Path, TSubclassOf<UDD_TableMapper> MapperType)
{
	const FString& TableName = DD_Utility::ConvertEnumToString<EDD_TableDataType>("ECY_TableDataType", TableType);

	if (TableMappers.Find(TableType))
	{
		return;
	}

	// 테이블 데이터 오브젝트 생성
	const TObjectPtr<UDataTable> TableObject = DD_Utility::LoadTableObjectFromFile(Path, TableName, FDD_LoadResourceDelegate::CreateUObject(this, &UDD_TableManager::LoadComplete));
	if (TableObject == nullptr)
	{
		return;
	}

	// 매퍼 생성 및 초기화
	if(MapperType)
	{
		const TObjectPtr<UDD_TableMapper> TableMapper = DD_NewObject<UDD_TableMapper>(this, MapperType);
		if (TableMapper == nullptr)
		{
			return;
		}
		// 추가.
		TableMappers.Emplace(TableType, FDD_TableMapperData(Path, TableObject, TableMapper));
		
		TableMapper->Initialize(this);
	}
	else
	{
		TableMappers.Emplace(TableType, FDD_TableMapperData(Path, TableObject, nullptr));
	}
}

void UDD_TableManager::MakeTableStructData()
{
	ResetData();
	
	CreateTableData(EDD_TableDataType::Common, "/Game/TableData/Common.Common", UDD_Mapper_Common::StaticClass());
	CreateTableData(EDD_TableDataType::Resource_Widget, "/Game/TableData/Common.Common", UDD_Mapper_Resource_Widget::StaticClass());
	
	CreateTableData(EDD_TableDataType::BasePath_Directory, "/Game/TableData/Common.Common");
	CreateTableData(EDD_TableDataType::BasePath_BP_File, "/Game/TableData/Common.Common");
	CreateTableData(EDD_TableDataType::BasePath_Img_File, "/Game/TableData/Common.Common");
	
	CreateTableData(EDD_TableDataType::PlayerStatus, "/Game/TableData/PlayerStatus.PlayerStatus", UDD_Mapper_PlayerStatus::StaticClass());
	CreateTableData(EDD_TableDataType::Enemy, "/Game/TableData/Enemy.Enemy", UDD_Mapper_Enemy::StaticClass());
}

void UDD_TableManager::LoadComplete(const FString& TableName, TObjectPtr<UObject> TableData)
{
}
