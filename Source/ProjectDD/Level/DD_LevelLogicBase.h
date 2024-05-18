// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DD_LevelLogicBase.generated.h"

UCLASS()
class PROJECTDD_API ADD_LevelLogicBase : public AActor
{
	GENERATED_BODY()

public:
	ADD_LevelLogicBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Level Logic")
	bool IsSettedBehaviorTree();

	UFUNCTION(BlueprintCallable, Category = "Level Logic")
	bool StopBehaviorTree();

	UFUNCTION(BlueprintCallable, Category = "Level Logic")
	bool StartBehaviorTree(bool bLoop = true);

	UFUNCTION(BlueprintCallable, Category = "Level Logic")
	bool PauseBehaviorTree();

	UFUNCTION(BlueprintCallable, Category = "Level Logic")
	bool IsPausedBehaviorTree();

	UFUNCTION(BlueprintCallable, Category = "Level Logic")
	void RemoveBehaviorTree();

	UFUNCTION(BlueprintCallable, Category = "Level Logic")
	bool SetBehaviorTree(FString Filename);

	bool SetBehaviorTreeAsset(class UBehaviorTree* _BTAsset);

	UPROPERTY(Category = DD_LevelLogicBase, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBehaviorTree> BTAsset = nullptr;

	UPROPERTY(Category = DD_LevelLogicBase, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBrainComponent> BrainComponent = nullptr;

	UPROPERTY(Category = DD_LevelLogicBase, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBlackboardComponent> BlackBoardComponent = nullptr;
};
