// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DD_Define.h"
#include "UObject/Object.h"
#include "DD_BasicUtilLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UDD_BasicUtilLibrary : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(const TObjectPtr<class UDD_GameInstance>& _GameInstance);
	void Finalize();
	
	static void ShowMessageOnScreen(const FString& Message, bool bNewerOnTop = true, float ElapsedTime = 3.f, FColor DisplayColor = FColor::Green);

	static TObjectPtr<AActor> SpawnBlueprintActor(const FString& BlueprintPath, const FVector& Pos, const FRotator& Rot, bool bNeedRootComponent = true,
												  ESpawnActorCollisionHandlingMethod Method = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);

	static TObjectPtr<UWorld> GetGameWorld();
	static TObjectPtr<UDD_GameInstance> GetGameInstance();
	static TObjectPtr<APlayerController> GetPlayerController();
	static TObjectPtr<FSceneViewport> GetGameViewport();
	static bool HasGameInstance();
	
private:
	static TObjectPtr<UDD_BasicUtilLibrary> ThisInstance;
	
	UPROPERTY()
	TObjectPtr<UDD_GameInstance> GameInstance = nullptr;



	//Todo. 용섭 : 인스턴스 생성 및 제거용(게임 인스턴스 들기용)
	
public:
	static TObjectPtr<UDD_BasicUtilLibrary> MakeInstance()
	{
		if(ThisInstance == nullptr)
		{
			ThisInstance = DD_NewObject<UDD_BasicUtilLibrary>();
			ThisInstance->AddToRoot();
		}
		return ThisInstance;
	}
	static void RemoveInstance()
	{
		if(ThisInstance != nullptr)
		{
			ThisInstance->RemoveFromRoot();
			ThisInstance->ConditionalBeginDestroy();
			ThisInstance = nullptr;
		}
	}
	static bool HasInstance()
	{
		return ThisInstance != nullptr ? true : false;
	}
	static TObjectPtr<UDD_BasicUtilLibrary> GetInstance()
	{
		return ThisInstance == nullptr ? nullptr : ThisInstance;
	}
};
