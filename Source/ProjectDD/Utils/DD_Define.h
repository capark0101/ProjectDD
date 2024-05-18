// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DD_Define.generated.h"

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

// Unit Type
typedef int32 DD_Handle;
constexpr int32 InvalidUnitHandle = 0;

DECLARE_MULTICAST_DELEGATE_OneParam(FDD_UnitActorTickDelegate, TObjectPtr<class UDD_UnitBase>);

USTRUCT(BlueprintType)
struct FDD_CharacterLodValues
{
   GENERATED_BODY()
 FDD_CharacterLodValues() {}

public:
 UPROPERTY(Category = "FDD_CharacterLodValues", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
 int32 CullDistance = 0;

 UPROPERTY(Category = "FDD_CharacterLodValues", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
 int32 OutLineCullDistance = 0;

 // not used
 UPROPERTY(Category = "FDD_CharacterLodValues", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true")) 
 int32 AnimMaxDistanceFactor = 0;

 UPROPERTY(Category = "FDD_CharacterLodValues", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
 TArray<float> AnimThresholdTable;

 UPROPERTY(Category = "FDD_CharacterLodValues", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
 int32 BaseNonRenderedUpdateRate = 0;

 float CullDistanceScale = 1.0f;
 float OutLineCullDistanceScale = 1.0f;
 bool  bVisibleOutLine = true;
};

UENUM(BlueprintType)
enum class EDD_UnitActionState : uint8
{
 None = 0			UMETA(DisplayName = "None"),
 Player_Normal				UMETA(DisplayName = "Player_Normal"),
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