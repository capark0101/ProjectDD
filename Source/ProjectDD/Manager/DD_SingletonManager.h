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
public:
	GENERATED_BODY()
	
	UDD_SingletonManager() {}
	virtual ~UDD_SingletonManager() override {}
	
	static UDD_SingletonManager* CreateInstance();
	static void DestroyInstance();
	static UDD_SingletonManager* GetInstance() { return Instance; }
	
	void BuiltInInitializeSingletons();

	void InitializeSingletons();
	void FinalizeSingletons();
	
	void TickSingletons(float DeltaTime);

	void RemoveSingletons();

protected:
	static UDD_SingletonManager* Instance;

private:
	void RegisterSingletons();
	void RegisterSingletonsForTick();
	
	bool bIsBuiltInInitialized = false;
	bool bInitialized = false;
	
	TArray<class ISingleton*> Singletons;
	TArray<class ISingleton*> SingletonsForTick;
};
