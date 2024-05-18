// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "DD_TableDefine.generated.h"

/**
 * 
 */

DECLARE_DELEGATE_TwoParams(FDD_LoadResourceDelegate, const FString&, TObjectPtr<UObject>);

UENUM()
enum class EDD_TableDataType : uint8
{
    Common = 0						UMETA(DisplayName = "Common"),
	Resource_Widget					UMETA(DisplayName = "Resource_Widget"),
	Resource_Unit					UMETA(DisplayName = "Resource_Unit"),

	BasePath_Directory				UMETA(DisplayName = "BasePath_Directory"),
	BasePath_BP_File				UMETA(DisplayName = "BasePath_BP_File"),
	BasePath_Img_File				UMETA(DisplayName = "BasePath_Img_File"),
	
	PlayerStatus					UMETA(DisplayName = "PlayerStatus"),
	Enemy							UMETA(DisplayName = "Enemy"),
};

USTRUCT()
struct FDD_TableMapperData
{
	GENERATED_USTRUCT_BODY()
public:
	FDD_TableMapperData() {}
	
	FDD_TableMapperData(const FString& _TablePath, const TObjectPtr<UDataTable>& _TableData, const TObjectPtr<class UDD_TableMapper>& _TableMapper) 
							: TablePath(_TablePath), TableData(_TableData), TableMapper(_TableMapper) {}
	~FDD_TableMapperData() { TableData = nullptr; TableMapper = nullptr; }

	void Finalize();
	
	FORCEINLINE const FString& GetTablePath() { return TablePath; }
	FORCEINLINE TObjectPtr<UDataTable> GetTableData() const { return TableData; }
	FORCEINLINE TObjectPtr<UDD_TableMapper> GetTableMapper() const { return TableMapper; }
private:
	FString TablePath = FString();
	
	UPROPERTY()
	TObjectPtr<UDataTable> TableData = nullptr;
	UPROPERTY()
	TObjectPtr<UDD_TableMapper> TableMapper = nullptr;
};