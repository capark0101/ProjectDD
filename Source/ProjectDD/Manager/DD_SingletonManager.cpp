﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_SingletonManager.h"
#include "DD_Singleton.h"
#include "DD_TableManager.h"
#include "Utils/DD_Define.h"

UDD_SingletonManager* UDD_SingletonManager::Instance = nullptr;

UDD_SingletonManager* UDD_SingletonManager::CreateInstance()
{
	Instance = DD_NewObject<UDD_SingletonManager>();
	Instance->AddToRoot();
	Instance->RegisterSingletons();
	Instance->RegisterSingletonsForTick();
	return Instance;
}

void UDD_SingletonManager::DestroyInstance()
{
	
	if (Instance != nullptr)
	{
		Instance->RemoveSingletons();
		Instance->RemoveFromRoot();
		DD_DeleteObject(Instance);
		Instance = nullptr;
	}
}

void UDD_SingletonManager::BuiltInInitializeSingletons()
{
	for (ISingleton* Singleton : Singletons)
	{
		Singleton->BuiltInInitialize();
	}

	bIsBuiltInInitialized = true;
}

void UDD_SingletonManager::InitializeSingletons()
{
	if(bInitialized)
	{
		return;
	}
    
	for (ISingleton* Singleton : Singletons)
	{
		Singleton->Initialize();
	}

	bInitialized = true;
}

void UDD_SingletonManager::FinalizeSingletons()
{
	if (bInitialized == false)
	{
		return;
	}

	for (ISingleton* Singleton : Singletons)
	{
		Singleton->PreFinalize();
		Singleton->Finalize();
		Singleton->BuiltInFinalize();
	}
}

void UDD_SingletonManager::TickSingletons(float DeltaTime)
{
	if (bInitialized)
	{
		for (ISingleton* Singleton : Singletons)
		{
			Singleton->Tick(DeltaTime);
		}
	}
}

void UDD_SingletonManager::RemoveSingletons()
{
	Singletons.Reset();
	SingletonsForTick.Reset();
	
	// [Class]::RemoveInstance();
	UDD_TableManager::RemoveInstance();
}

void UDD_SingletonManager::RegisterSingletons()
{
	Singletons.Reset();

	// Singletons.Emplace([Class]::MakeInstance());
	Singletons.Emplace(UDD_TableManager::MakeInstance());
}

void UDD_SingletonManager::RegisterSingletonsForTick()
{
	SingletonsForTick.Reset();

	// SingletonsForTick.Emplace([Class]::GetInstance());
	SingletonsForTick.Emplace(UDD_TableManager::GetInstance());
}