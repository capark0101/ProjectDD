// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DD_StateMachine.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UDD_StateMachine : public UObject
{
	GENERATED_BODY()

public:
	void Create();
	void Destroy();
	void Tick(float DeltaTime);

	void RegistState(int8 Index, const FName& Name, TSubclassOf<class UDD_StateBase> Type, UObject* Outer = nullptr);
	void UnRegistEntireStates();

	TObjectPtr<UDD_StateBase> GetCurrentState();

	void GetEntireStateIds(TArray<int8>& Indices) const;

	void SetState(int32 Index, bool bInstant = true);

	FORCEINLINE TObjectPtr<UDD_StateBase> GetState(int32 Index) const;
	
private:
	void SetState_Internal(uint8 Index);
	
	UPROPERTY()
	TMap<int8, TObjectPtr<UDD_StateBase>> EntireStates;

	uint8 PreviousStateId = -1;
	uint8 CurrentStateId = -1;
	uint8 ChangeStateId = -1;
};
