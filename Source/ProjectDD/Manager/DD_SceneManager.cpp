// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_SceneManager.h"

#include "DD_BasicUtilLibrary.h"
//#include "DD_CameraManager.h"
//#include "DD_WidgetManager.h"
#include "DD_StateMachine.h"
#include "DD_Define.h"
#include "DD_FadeCommand.h"
#include "DD_FadeSceneTool.h"
#include "DD_InputManager.h"
#include "DD_LevelLogicBase.h"
#include "DD_SceneBT.h"
#include "DD_Utility.h"
#include "EngineUtils.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Kismet/GameplayStatics.h"
#include "ScaeneState/DD_SceneState_Lobby.h"
#include "ScaeneState/DD_SceneState_Logo.h"

UDD_SceneManager::UDD_SceneManager()
{
}

UDD_SceneManager::~UDD_SceneManager()
{
}

void UDD_SceneManager::BuiltInInitialize()
{
	TDD_Singleton<UDD_SceneManager>::BuiltInInitialize();

	if(SceneStateMachine)
	{
		return;
	}
	
	SceneStateMachine = DD_NewObject<UDD_StateMachine>(this, UDD_StateMachine::StaticClass());
	SceneStateMachine->AddToRoot();
	SceneStateMachine->Create();
}

void UDD_SceneManager::Initialize()
{
	TDD_Singleton<UDD_SceneManager>::Initialize();

	FadeTool = DD_NewObject<UDD_FadeSceneTool>();
	if(IsValid(FadeTool))
	{
		FadeTool->Initialize();
		
		TArray<int8> ActiveSceneId;
		SceneStateMachine->GetEntireStateIds(ActiveSceneId);

		for(const int8 SceneId : ActiveSceneId)
		{
			FadeTool->RegistLevelPath(SceneId);
		}
	}
}

void UDD_SceneManager::PostInitialize()
{
	TDD_Singleton<UDD_SceneManager>::PostInitialize();

	if(IsValid(FadeTool))
	{
		FadeTool->Initialize();
	}
}

void UDD_SceneManager::Finalize()
{
	TDD_Singleton<UDD_SceneManager>::Finalize();

	DD_DeleteObject(FadeTool);
	FadeTool = nullptr;
	
	LoadLevelInitialized.Unbind();
	LoadLevelInitialized = nullptr;
	
	UnregisterSceneBehaviorTree();
}

void UDD_SceneManager::BuiltInFinalize()
{
	TDD_Singleton<UDD_SceneManager>::BuiltInFinalize();

	SceneStateMachine->Destroy();
	SceneStateMachine->RemoveFromRoot();
	SceneStateMachine = nullptr;
}

void UDD_SceneManager::Tick(float DeltaTime)
{
	TDD_Singleton<UDD_SceneManager>::Tick(DeltaTime);

	if(IsValid(FadeTool))
	{
		FadeTool->Tick(DeltaTime);
	}
	
	if(ChangeSceneData.Step == EDD_ChangeSceneStep::Complete)
	{
		if (SceneStateMachine)
		{
			SceneStateMachine->Tick(DeltaTime);
		}	
	}
	else if(ChangeSceneData.Step == EDD_ChangeSceneStep::PrepareSceneState)
	{
		const TObjectPtr<UDD_SceneBase> CurrentScene = GetCurrentScene();
		if(IsValid(CurrentScene) == false)
		{
			return;
		}
		
		CurrentScene->TickLoading(DeltaTime);

		if(CurrentScene->IsCompleteLoading())
		{
			ChangeSceneData.Step = EDD_ChangeSceneStep::Complete;
		}
	}
}

TObjectPtr<UDD_SceneBase> UDD_SceneManager::GetCurrentScene() const
{
	if(SceneStateMachine)
	{
		return Cast<UDD_SceneBase>(SceneStateMachine->GetCurrentState());
	}

	return nullptr;
}

void UDD_SceneManager::RegisterScenes() const
{
	RegistSceneState(static_cast<uint8>(EDD_GameSceneType::Logo), TEXT("Logo"), UDD_SceneState_Logo::StaticClass());
	RegistSceneState(static_cast<uint8>(EDD_GameSceneType::Lobby), TEXT("Lobby"), UDD_SceneState_Lobby::StaticClass());
}

void UDD_SceneManager::SceneLoadComplete(float LoadTime, const FString& LevelName)
{
	gInputMng.CreateInputPawn();
	ActiveLevels.Empty();

	const TObjectPtr<UWorld> World = UDD_BasicUtilLibrary::GetGameWorld();
	const TArray<ULevelStreaming*>& Levels = World->GetStreamingLevels();

	for(int32 i = 0 ; i < Levels.Num() ; i++)
	{
		if(World->GetCurrentLevel()->GetName().Equals(Levels[i]->PackageNameToLoad.ToString(), ESearchCase::IgnoreCase))
		{
			ActiveLevels.Emplace(Levels[i]->PackageNameToLoad.ToString(), true);
		}
		else
		{
			ActiveLevels.Emplace(Levels[i]->PackageNameToLoad.ToString(), false);
		}
	}

	ExecuteLoadLevelDelegate(LevelName);
}

void UDD_SceneManager::ExecuteLoadLevelDelegate(const FString& LevelName)
{
	if(LoadLevelInitialized.IsBound())
	{
		const FDD_LoadLevelInitialized Delegate = LoadLevelInitialized;
		LoadLevelInitialized.Unbind();
		
		Delegate.Execute(LevelName.IsEmpty() ? UDD_BasicUtilLibrary::GetGameWorld()->GetMapName() : LevelName);
	}
}

bool UDD_SceneManager::LoadLevelByPath(const FDD_LoadLevelInitialized& Delegate, const FName& PackagePath,
	bool bAbsolute)
{
	if(UDD_BasicUtilLibrary::HasGameInstance() == false)
	{
		return false;
	}

	const TObjectPtr<UWorld> World = UDD_BasicUtilLibrary::GetGameWorld();
	if(World == nullptr)
	{
		return false;
	}

	gInputMng.DestroyInputPawn();
	//gCameraMng.DestroyAllCameras();

	UGameplayStatics::OpenLevel(World, PackagePath, bAbsolute);

	LoadLevelInitialized.Unbind();
	LoadLevelInitialized = Delegate;

	return true;
}

bool UDD_SceneManager::LoadLevelBySoftObjectPtr(const TSoftObjectPtr<UWorld>& LevelObjectPtr,
	const FDD_LoadLevelInitialized& Delegate)
{
	const TObjectPtr<UWorld> World = UDD_BasicUtilLibrary::GetGameWorld();
	if(IsValid(World) == false)
	{
		return false;
	}

	gInputMng.DestroyInputPawn();
	//gCameraMng.DestroyAllCameras();

	bool bSuccess = true;
	ULevelStreamingDynamic::LoadLevelInstanceBySoftObjectPtr(World, LevelObjectPtr, FVector::ZeroVector, FRotator::ZeroRotator, bSuccess);

	if(bSuccess)
	{
		LoadLevelInitialized.Unbind();
		LoadLevelInitialized = Delegate;
	}

	return true;
}

void UDD_SceneManager::ChangeScene(EDD_GameSceneType SceneType, TObjectPtr<UDD_FadeCommand> Command)
{
	if(OnChangeScene.IsBound())
	{
		OnChangeScene.Broadcast(SceneType);
	}

	const FString LevelPackagePath = Command != nullptr ? FadeTool->GetLevelPath(SceneType) : FString();
	
	DD_LOG(TEXT("UDD_SceneManager::ChangeScene - SceneId(%d), LevelPath(%s)"), SceneType, *LevelPackagePath);
	
	ChangeSceneData.Step = EDD_ChangeSceneStep::Ready;
	ChangeSceneData.SceneType = SceneType;
	ChangeSceneData.LevelPackagePath = FName(LevelPackagePath);

	if(Command != nullptr)
	{
		ChangeSceneStep_Fade(Command);
	}
	else
	{
		ChangeSceneStep_LoadLevel();
	}

	//gWidgetMng.ClearExclusiveLayer();
}

void UDD_SceneManager::SetSceneBehaviorTreeAsset(TObjectPtr<UBehaviorTree> BTAsset)
{
}

void UDD_SceneManager::RegistSceneBehaviorTree()
{
}

void UDD_SceneManager::RegistSceneState(uint8 SceneId, const FName& Name, TSubclassOf<UDD_StateBase> SceneType) const
{
	SceneStateMachine->RegistState(SceneId, Name, SceneType);
}

bool UDD_SceneManager::ChangeSceneStep_Fade(TObjectPtr<UDD_FadeCommand> Command)
{
	if(Command == nullptr)
	{
		return false;
	}

	if(ChangeSceneData.Step == EDD_ChangeSceneStep::Ready)
	{
		Command->OnFadeOutComplete = FDD_FadeEventDelegate::CreateWeakLambda(this, [this]()
			{
				ChangeSceneStep_LoadLevel();
			});
		
		ChangeSceneData.Step = EDD_ChangeSceneStep::PlayFade;
		FadeTool->Request(Command);
		return true;
	}
	return false;
}

bool UDD_SceneManager::ChangeSceneStep_LoadLevel()
{
	if(ChangeSceneData.LevelPackagePath == NAME_None)
	{
		ChangeSceneStep_SetSceneState(static_cast<uint8>(ChangeSceneData.SceneType));
		return true;
	}
	
	ChangeSceneData.Step = EDD_ChangeSceneStep::StartLoadLevel;

	UnregisterSceneBehaviorTree();
	//gCameraMng.ResetData();
	OnStartLevelLoading.Broadcast(ChangeSceneData.LevelPackagePath.ToString());

	return LoadLevelByPath(FDD_LoadLevelInitialized::CreateUObject(this, &UDD_SceneManager::OnCompleteLevelLoading), ChangeSceneData.LevelPackagePath, true);
}

void UDD_SceneManager::ChangeSceneStep_SetSceneState(uint8 SceneId)
{
	ChangeSceneData.Step = EDD_ChangeSceneStep::PrepareSceneState;

	//SceneStateMachine->GetState(SceneId);
	if(SceneStateMachine)
	{
		SceneStateMachine->SetState(SceneId);
	}
}

void UDD_SceneManager::OnCompleteLevelLoading(const FString& LevelPackagePath)
{
	RegisterSceneBehaviorTree();

	ChangeSceneStep_SetSceneState(static_cast<uint8>(ChangeSceneData.SceneType));

	OnFinishedLevelLoading.Broadcast(LevelPackagePath);
}

void UDD_SceneManager::RegisterSceneBehaviorTree()
{
	if(SceneLogic != nullptr)
	{
		return;
	}

	if(SceneBehaviorTree == nullptr)
	{
		return;
	}

	if(UDD_BasicUtilLibrary::HasGameInstance() == false)
	{
		return;
	}

	for (TActorIterator<ADD_LevelLogicBase> it(UDD_BasicUtilLibrary::GetGameWorld()); it; ++it)
	{
		if (it->GetName().Equals(TEXT("SceneLogicActor"), ESearchCase::IgnoreCase) == true) {
			SceneLogic = *it;
			break;
		}
	}

	if (SceneLogic != nullptr)
	{
		if (SceneLogic->SetBehaviorTreeAsset(SceneBehaviorTree))
			SceneLogic->StartBehaviorTree();
	}
	else
	{
		SceneLogic = Cast<ADD_LevelLogicBase>(UDD_BasicUtilLibrary::GetGameWorld());
		if (SceneLogic)
		{
			if (SceneLogic->SetBehaviorTreeAsset(SceneBehaviorTree))
				SceneLogic->StartBehaviorTree();
		}
	}
}

void UDD_SceneManager::UnregisterSceneBehaviorTree()
{
	if(SceneLogic != nullptr)
	{
		SceneLogic->RemoveBehaviorTree();
		SceneLogic = nullptr;
	}
	if(CustomSceneBT)
	{
		CustomSceneBT->StopBT();
		CustomSceneBT = nullptr;
	}
}
