// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Utils/DD_Define.h"
#include "DD_Singleton.h"

template<typename TClass>
TObjectPtr<TClass> TDD_Singleton<TClass>::MakeInstance()
{
	if(Instance != nullptr)
	{
		return nullptr;
	}

	Instance = DD_NewObject<TClass>();
	Instance->AddToRoot();
	return Instance;
}

template<typename TClass>
void TDD_Singleton<TClass>::RemoveInstance()
{
	if(Instance == nullptr)
	{
		return;
	}

	if(Instance->IsValidLowLevel())
	{
		Instance->RemoveFromRoot();
		DD_DeleteObject(Instance);
	}

	Instance = nullptr;
}

template<typename TClass>
TObjectPtr<TClass> TDD_Singleton<TClass>::GetInstance()
{
	return Instance;
}

template<typename TClass>
bool TDD_Singleton<TClass>::HasInstance()
{
	return Instance != nullptr && !Instance->HasAnyFlags(RF_FinishDestroyed);
}