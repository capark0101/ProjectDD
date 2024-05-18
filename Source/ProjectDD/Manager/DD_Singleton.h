// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"

/**
 * 
 */
class ISingleton
{
public:
	virtual ~ISingleton() {}

	virtual void BuiltInInitialize() {}
	virtual void Initialize() {}
	virtual void PostInitialize() {}
	virtual void PreFinalize() {}
	virtual void Finalize() {}
	virtual void BuiltInFinalize() {}

	virtual void Tick(float _DeltaTime) {}
};

template<typename TClass>
class PROJECTDD_API TDD_Singleton : public ISingleton
{
protected:
	static TClass* Instance;

public:
	static TClass* MakeInstance();
	static void RemoveInstance();
	static TClass* GetInstance();
	static bool HasInstance();
};

template<typename TClass>
TClass* TDD_Singleton<TClass>::Instance = nullptr;

#include "DD_Singleton.inl"