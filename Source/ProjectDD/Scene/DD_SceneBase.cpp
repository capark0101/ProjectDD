// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_SceneBase.h"

void UDD_SceneBase::Begin()
{
	Super::Begin();

	LoadingProcessDelegates.Empty();
	LoadingProcessDelegates.Add(FDD_LoadingProcessDelegate::CreateUObject(this, &UDD_SceneBase::LoadingPreProcess));
	LoadingProcessDelegates.Add(FDD_LoadingProcessDelegate::CreateUObject(this, &UDD_SceneBase::LoadingProcess));
	LoadingProcessDelegates.Add(FDD_LoadingProcessDelegate::CreateUObject(this, &UDD_SceneBase::LoadingPostProcess));
}

void UDD_SceneBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void UDD_SceneBase::Exit()
{
	Super::Exit();

	LoadingProcessDelegates.Empty();
}

void UDD_SceneBase::TickLoading(float DeltaTime)
{
	if (LoadingProcessDelegates.IsValidIndex(0) == true)
	{
		if (LoadingProcessDelegates[0].Execute(DeltaTime) == true)
		{
			LoadingProcessDelegates.RemoveAt(0);
		}
	}
}

bool UDD_SceneBase::IsCompleteLoading()
{
	return LoadingProcessDelegates.Num() <= 0;
}

bool UDD_SceneBase::LoadingPreProcess(float DeltaTime)
{
	return true;
}

bool UDD_SceneBase::LoadingProcess(float DeltaTime)
{
	return true;
}

bool UDD_SceneBase::LoadingPostProcess(float DeltaTime)
{
	return true;
}
