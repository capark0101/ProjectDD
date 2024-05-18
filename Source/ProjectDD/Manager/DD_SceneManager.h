// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Scene/DD_SceneBase.h"
#include "Scene/DD_SceneDefine.h"
#include "DD_Singleton.h"
#include "DD_SceneManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UDD_SceneManager : public UObject, public TDD_Singleton<UDD_SceneManager>
{
	GENERATED_BODY()

public:
	UDD_SceneManager();
	~UDD_SceneManager();

	virtual void BuiltInInitialize() override;
	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Finalize() override;
	virtual void BuiltInFinalize() override;
	virtual void Tick(float DeltaTime) override;
	
	TObjectPtr<UDD_SceneBase> GetCurrentScene() const;

	FORCEINLINE bool IsCompleteChangeScene() const { return ChangeSceneData.Step == EDD_ChangeSceneStep::Complete; }

	void RegisterScenes() const;
	void SceneLoadComplete(float LoadTime, const FString& LevelName);
	void ExecuteLoadLevelDelegate(const FString& LevelName = TEXT(""));
	
	bool LoadLevelByPath(const FDD_LoadLevelInitialized& Delegate, const FName& PackagePath = FName(), bool bAbsolute = true);
	bool LoadLevelBySoftObjectPtr(const TSoftObjectPtr<UWorld>& LevelObjectPtr, const FDD_LoadLevelInitialized& Delegate);
	
	void ChangeScene(EDD_GameSceneType SceneType, TObjectPtr<class UDD_FadeCommand> Command = nullptr);
	void SetSceneBehaviorTreeAsset(TObjectPtr<class UBehaviorTree> BTAsset);
	void RegistSceneBehaviorTree();

	FDD_ChangeSceneDelegate OnChangeScene;
	FDD_LoadLevelDelegate OnStartLevelLoading;
	FDD_LoadLevelDelegate OnFinishedLevelLoading;
	FDD_ChangeSceneState OnCompleteChangeScene;

	FDD_LoadLevelInitialized LoadLevelInitialized;
	
private:
	void RegistSceneState(uint8 SceneId, const FName& Name, TSubclassOf<class UDD_StateBase> SceneType) const;

	bool ChangeSceneStep_Fade(TObjectPtr<UDD_FadeCommand> Command);
	bool ChangeSceneStep_LoadLevel();
	void ChangeSceneStep_SetSceneState(uint8 SceneId);
	void OnCompleteLevelLoading(const FString& LevelPackagePath);

	void RegisterSceneBehaviorTree();
	void UnregisterSceneBehaviorTree();
	
	UPROPERTY()
	TMap<FString, bool> ActiveLevels;
	
	UPROPERTY()
	TObjectPtr<UDD_StateMachine> SceneStateMachine = nullptr;

	UPROPERTY()
	FDD_ChangeSceneData ChangeSceneData;

	UPROPERTY()
	TObjectPtr<class ADD_LevelLogicBase> SceneLogic = nullptr;

	UPROPERTY()
	TObjectPtr<UBehaviorTree> SceneBehaviorTree = nullptr;
	
	UPROPERTY()
	TObjectPtr<class ADD_SceneBT> CustomSceneBT = nullptr;
	
	UPROPERTY()
	TObjectPtr<class UDD_FadeSceneTool> FadeTool = nullptr;
	
#define	gSceneMng (*UDD_SceneManager::GetInstance())
};
