// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DD_StateBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UDD_StateBase : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(uint8 Index, const FName& Name);
	virtual void Finalize();
	virtual void Tick(float DeltaTime);
	
	UFUNCTION()
	void OnBeginState();
	UFUNCTION()
	void OnExitState();
	
	FORCEINLINE uint8 GetStateIndex() const { return StateIndex; }
	FORCEINLINE FName GetStateName() const { return StateName; }

	TObjectPtr<class UDD_StateMachine> GetStateMachine() const;

protected:
	virtual void Begin() {}
	virtual void Exit() {}

private:	
	UPROPERTY()
	int32 StateIndex = -1;
	UPROPERTY()
	FName StateName = {};
};
