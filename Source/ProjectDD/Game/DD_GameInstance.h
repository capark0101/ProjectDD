// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "Utils/DD_Define.h"
#include "DD_GameInstance.generated.h"

/**
 * 
 */
UCLASS(Config=Game)
class PROJECTDD_API UDD_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UDD_GameInstance();
	virtual ~UDD_GameInstance() override;

	virtual void Init() override;
	virtual void Shutdown() override;

	virtual void OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld) override;
	virtual void LoadComplete(const float LoadTime, const FString& MapName) override;

	bool Tick(float DeltaSeconds);

	FORCEINLINE FStreamableManager& GetAssetLoader() { return AssetLoader; }
	
private:
	void OnStartGameInstance(UGameInstance* GameInstance);
	
	void ProcessInitialize();
	void ProcessFinalize();

	bool CreateBasicUtility();
	bool DestroyBasicUtility();
	
	bool CreateManagers();
	bool DestroyManagers();

	bool RegisterTick();
	bool UnRegisterTick();

	bool RegisterState();

	bool LoadBaseWorld();
	bool UnLoadBaseWorld();

	void RestartGame();
	
	UPROPERTY(Category = UCY_GameInstance, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UWorld> BaseWorld;
	
	FTSTicker::FDelegateHandle TickDelegateHandle;

	EDD_LaunchProcessType ProcessType = EDD_LaunchProcessType::None;

	FStreamableManager AssetLoader;
};
