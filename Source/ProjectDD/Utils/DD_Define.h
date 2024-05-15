// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "DD_Define.generated.h"

/**
 * 
 */
DECLARE_LOG_CATEGORY_EXTERN(DD_Log, Log, All);

#define DD_LOG(InFormat, ...) UE_LOG(DD_Log, Log, InFormat, ##__VA_ARGS__)

#define DD_CHECK(expr) check(expr)

// Object
#define DD_NewObject NewObject

#define DD_DeleteObject(Object) {			\
DD_CHECK(Object != nullptr);					   \
Object->ConditionalBeginDestroy();	 \
};

// GameInstance
UENUM(BlueprintType)
enum class EDD_LaunchProcessType : uint8
{
 None = 0,
 
 CreateBasicUtility,
 CreateManager,
 RegistTick,
 RegistState,
 LoadBaseWorld,
 ProcessFinished,

 End
};