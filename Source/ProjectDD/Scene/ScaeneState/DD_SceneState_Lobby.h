// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DD_SceneBase.h"
#include "DD_SceneState_Lobby.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UDD_SceneState_Lobby : public UDD_SceneBase
{
	GENERATED_BODY()
	
protected:
	virtual void Begin() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Exit() override;
};
