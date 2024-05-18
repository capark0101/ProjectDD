// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DD_BasicUtilLibrary.h"
#include "Table/DD_TableDefine.h"

/**
 * 
 */
namespace DD_Utility
{
	TObjectPtr<AActor> SpawnActor(UClass* Class, const FVector& Location, const FRotator& Rotation, const FString &LabelName, ESpawnActorCollisionHandlingMethod CollisionMathod, bool bNeedRootComponent);
	
	// todo 용섭 : Enum 을 FString 으로 변환하는 메소드
	template<typename TEnum>
	static FString ConvertEnumToString(const FString& EnumString, TEnum EnumType)
	{
		const UEnum* pEnum = FindObject<UEnum>(UDD_BasicUtilLibrary::GetGameWorld(), *EnumString, true);
		if (!pEnum)
		{
			return FString("");
		}

		const int32 Index = pEnum->GetIndexByValue(static_cast<int32>(EnumType));
		return pEnum->GetNameStringByIndex(Index);
	}

	template<typename T>
	static TObjectPtr<T> GetSafeMapValue(TObjectPtr<T>* pMapValue)
	{
		return (pMapValue == nullptr) ? nullptr : *pMapValue;	
	};


	static const TCHAR* AttachPathAsName(FString AssetPath, FString AssetName);
	FString GetBPNameFromFullPath(const FString& FullPath);

	FRotator MakeRotatorFromForward(const FVector& ForwardVector);

	TObjectPtr<UDataTable> LoadTableObjectFromFile(const FString& ResourcePath, const FString& TableName, FDD_LoadResourceDelegate Delegate);
	TObjectPtr<UObject> LoadObjectFromFile(const FString& ResourcePath, const FDD_LoadResourceDelegate& Delegate = nullptr, const FString& SubName = TEXT("SubName"), int32 Index = 0, bool SubBool = false);
};