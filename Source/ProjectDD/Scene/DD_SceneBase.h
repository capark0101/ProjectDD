// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateMachine/DD_StateBase.h"
#include "DD_SceneBase.generated.h"

/**
 * 
 */
DECLARE_DELEGATE_RetVal_OneParam(bool, FDD_LoadingProcessDelegate, float);

UCLASS()
class PROJECTDD_API UDD_SceneBase : public UDD_StateBase
{
	GENERATED_BODY()

protected:
	virtual void Begin() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Exit() override;

public:
	void TickLoading(float DeltaTime);
	bool IsCompleteLoading();

protected:
	virtual bool LoadingPreProcess(float DeltaTime);
	virtual bool LoadingProcess(float DeltaTime);
	virtual bool LoadingPostProcess(float DeltaTime);

private:
	TArray<FDD_LoadingProcessDelegate> LoadingProcessDelegates;
};
