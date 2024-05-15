// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DD_SingletonManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UDD_SingletonManager : public UObject
{
	GENERATED_BODY()

public:
	static TObjectPtr<UDD_SingletonManager> CreateInstance();
	static void DestroyInstance();
	static TObjectPtr<UDD_SingletonManager> GetInstance() { return Instance; }
	
	void BuiltInInitializeSingletons();

	void InitializeSingletons();
	void FinalizeSingletons();
	
	void TickSingletons(float DeltaTime);

	void RemoveSingletons();

protected:
	static TObjectPtr<UDD_SingletonManager> Instance;

private:
	void RegisterSingletons();
	void RegisterSingletonsForTick();
	
	bool bIsBuiltInInitialized = false;
	bool bInitialized = false;
	
	TArray<TSharedPtr<class ISingleton>> Singletons;
	TArray<TSharedPtr<class ISingleton>> SingletonsForTick;
};
