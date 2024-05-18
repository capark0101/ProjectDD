// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DD_SceneBT.generated.h"

UCLASS()
class PROJECTDD_API ADD_SceneBT : public AActor
{
	GENERATED_BODY()

public:
	ADD_SceneBT();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	bool CreateBT(const FString& BTPath);
	void DestroyBT();
	void StartBT() const;
	void StopBT() const;
	void PauseBT() const;
	void ResumeBT() const;

public:
	UPROPERTY()
	TObjectPtr<class UBehaviorTree> BTAsset = nullptr;
	UPROPERTY()
	TObjectPtr<class UBlackboardComponent> BlackboardComponent = nullptr;
	UPROPERTY()
	TObjectPtr<class UBehaviorTreeComponent> BTComponent = nullptr;
};
