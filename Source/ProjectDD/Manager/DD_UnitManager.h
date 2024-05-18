// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DD_Singleton.h"
#include "DD_Define.h"
#include "UObject/Object.h"
#include "DD_UnitManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UDD_UnitManager : public UObject, public TDD_Singleton<UDD_UnitManager>
{
	GENERATED_BODY()
public:
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Tick(float _DeltaTime) override;

	TObjectPtr<class UDD_UnitBase> CreateUnit(int32 UnitTableId, const TSubclassOf<UDD_UnitBase>& UnitType, const FVector& Position = FVector::ZeroVector, const FRotator& Rotator = FRotator::ZeroRotator);

	void DestroyUnit(DD_Handle UnitHandle);
	void DestroyAllUnit();

	TObjectPtr<class ADD_CharacterBase> CreateCharacter(const FString& BlueprintPath, const FVector& Pos, const FRotator& Rot);

	TObjectPtr<UDD_UnitBase> GetUnit(DD_Handle UnitHandle);
	DD_Handle GetUnitHandle(const TObjectPtr<UDD_UnitBase>& UnitBase) const;
	
	TObjectPtr<ADD_CharacterBase> GetCharacterBase(DD_Handle UnitHandle);

private:
	DD_Handle MakeUnitHandle(const TObjectPtr<UDD_UnitBase>& Unit) const;
	
	TMap<DD_Handle, TObjectPtr<UDD_UnitBase>> Units;

	float LodScale = 1.f;
	bool bOutLineModeOn = true;

#define gUnitMng (*UDD_UnitManager::GetInstance())
};
