// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_BasicUtilLibrary.h"

#include "DD_Utility.h"
#include "Game/DD_GameInstance.h"
#include "Kismet/GameplayStatics.h"

TObjectPtr<UDD_BasicUtilLibrary> UDD_BasicUtilLibrary::ThisInstance = nullptr;

void UDD_BasicUtilLibrary::Initialize(const TObjectPtr<UDD_GameInstance>& _GameInstance)
{
	GameInstance = _GameInstance;
}

void UDD_BasicUtilLibrary::Finalize()
{
	GameInstance = nullptr;
}

void UDD_BasicUtilLibrary::ShowMessageOnScreen(const FString& Message, bool bNewerOnTop, float ElapsedTime, FColor DisplayColor)
{
	GEngine->AddOnScreenDebugMessage(-1, ElapsedTime, DisplayColor, Message);
}

TObjectPtr<AActor> UDD_BasicUtilLibrary::SpawnBlueprintActor(const FString& BlueprintPath, const FVector& Pos, const FRotator& Rot, bool bNeedRootComponent, ESpawnActorCollisionHandlingMethod Method)
{
	UClass* BlueprintClass = StaticLoadClass(UObject::StaticClass(), nullptr, *BlueprintPath);
	if(IsValid(BlueprintClass) == false)
	{
		DD_CHECK(false);
		DD_LOG(TEXT("Blueprint Path or Name is not Correct. Please Check Blueprint Path"));
		return nullptr;
	}
	
	const TObjectPtr<UWorld> World = GetGameWorld();
	if(IsValid(World) == false)
	{
		return nullptr;	
	}
			
	FActorSpawnParameters Parameters;
	Parameters.OverrideLevel = World->GetCurrentLevel();
	Parameters.SpawnCollisionHandlingOverride = Method;
	const TObjectPtr<AActor> ResultActor = World->SpawnActor(BlueprintClass, &Pos, &Rot, Parameters);

	if(ResultActor)
	{
		ResultActor->SetActorLabel(DD_Utility::GetBPNameFromFullPath(BlueprintPath));

		if(bNeedRootComponent && ResultActor->GetRootComponent() == nullptr)
		{
			const TObjectPtr<USceneComponent> RootComponent = NewObject<USceneComponent>(ResultActor, USceneComponent::GetDefaultSceneRootVariableName(), RF_Transactional);
			RootComponent->Mobility = EComponentMobility::Movable;

			ResultActor->SetRootComponent(RootComponent);
			ResultActor->AddInstanceComponent(RootComponent);

			RootComponent->RegisterComponent();
		}
	}

	return ResultActor != nullptr ? ResultActor : nullptr;
}

TObjectPtr<UWorld> UDD_BasicUtilLibrary::GetGameWorld()
{
	return ThisInstance ? ThisInstance->GameInstance ? ThisInstance->GameInstance->GetWorld() : nullptr : nullptr;
}

TObjectPtr<UDD_GameInstance> UDD_BasicUtilLibrary::GetGameInstance()
{
	return ThisInstance->GameInstance == nullptr ? nullptr : ThisInstance->GameInstance;
}

TObjectPtr<APlayerController> UDD_BasicUtilLibrary::GetPlayerController()
{
	const TObjectPtr<UWorld> World = GetGameWorld();
	if(World == nullptr)
	{
		return nullptr;
	}

	const TObjectPtr<APlayerController> Controller = UGameplayStatics::GetPlayerController(World, 0);

	return Controller ? Controller : nullptr;
}

TObjectPtr<FSceneViewport> UDD_BasicUtilLibrary::GetGameViewport()
{
	if(GEngine && GEngine->GameViewport)
	{
		return GEngine->GameViewport->GetGameViewport();
	}

	return nullptr;
}

bool UDD_BasicUtilLibrary::HasGameInstance()
{
	return ThisInstance->GameInstance != nullptr;
}
