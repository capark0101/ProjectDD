// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_Utility.h"

#include "DD_BasicUtilLibrary.h"
#include "Game/DD_GameInstance.h"
#include "Kismet/KismetMathLibrary.h"

TObjectPtr<AActor> DD_Utility::SpawnActor(UClass* Class, const FVector& Location, const FRotator& Rotation, const FString& LabelName, ESpawnActorCollisionHandlingMethod CollisionMathod, bool bNeedRootComponent)
{
	const TObjectPtr<UWorld> World = UDD_BasicUtilLibrary::GetGameWorld();

	if (World == nullptr || Class == nullptr)
	{
		return nullptr;
	}
	AActor* NewActor = nullptr;
	
	FActorSpawnParameters Params;
	Params.OverrideLevel = World->GetCurrentLevel();
	Params.SpawnCollisionHandlingOverride = CollisionMathod;
	NewActor = World->SpawnActor(Class, &Location, &Rotation, Params);
	if (NewActor)
	{
#if WITH_EDITOR
		if (LabelName.IsEmpty() == false)
			NewActor->SetActorLabel(LabelName);
#endif

		if ((bNeedRootComponent == true) && (NewActor->GetRootComponent() == nullptr))
		{
			USceneComponent* RootComponent = NewObject<USceneComponent>(NewActor, USceneComponent::GetDefaultSceneRootVariableName(), RF_Transactional);
			RootComponent->Mobility = EComponentMobility::Movable;
#if WITH_EDITORONLY_DATA
			RootComponent->bVisualizeComponent = false;
#endif
			NewActor->SetRootComponent(RootComponent);
			NewActor->AddInstanceComponent(RootComponent);

			RootComponent->RegisterComponent();
		}
	}

	return NewActor;
}

const TCHAR* DD_Utility::AttachPathAsName(FString AssetPath, FString AssetName)
{
	AssetPath.Append(AssetName);
	AssetPath.Append(TEXT("."));
	AssetPath.Append(AssetName);

	return *AssetPath;
}

FString DD_Utility::GetBPNameFromFullPath(const FString& FullPath)
{
	if(FullPath.IsEmpty())
	{
		return FString();
	}

	int32 LastPoint = 0;
	int32 LastSlash = 0;
	constexpr TCHAR Point = '.';
	constexpr TCHAR Slash = '/';
	FullPath.FindLastChar(Point, LastPoint);
	FullPath.FindLastChar(Slash, LastSlash);

	return FullPath.Mid(LastSlash + 1, LastPoint - LastSlash - 1);
}

FRotator DD_Utility::MakeRotatorFromForward(const FVector& ForwardVector)
{
	return UKismetMathLibrary::MakeRotFromX(ForwardVector);
}

TObjectPtr<UDataTable> DD_Utility::LoadTableObjectFromFile(const FString& ResourcePath, const FString& TableName, FDD_LoadResourceDelegate Delegate)
{
	const TObjectPtr<UDataTable> ResultObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ResourcePath, *ResourcePath, LOAD_None, nullptr));

	if(Delegate.IsBound())
	{
		Delegate.Execute(TableName, ResultObject);
	}
	
	return ResultObject;
}

TObjectPtr<UObject> DD_Utility::LoadObjectFromFile(const FString& ResourcePath, const FDD_LoadResourceDelegate& Delegate, const FString& SubName, int32 Index, bool SubBool)
{
	const FSoftObjectPath Reference = ResourcePath;
	
	UObject* ResultObject = UDD_BasicUtilLibrary::GetGameInstance()->GetAssetLoader().LoadSynchronous(Reference);
	if(Delegate.IsBound())
	{
		Delegate.Execute(ResourcePath, ResultObject);
	}
	return ResultObject;
}
