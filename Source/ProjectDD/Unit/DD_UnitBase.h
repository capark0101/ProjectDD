// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DD_CharacterBase.h"
#include "DD_Define.h"
#include "DD_StateMachine.h"
#include "UObject/Object.h"
#include "DD_UnitBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDD_API UDD_UnitBase : public UObject
{
	GENERATED_BODY()
public:
	virtual void Initialize();
	virtual void Finalize();
	virtual void Tick(float DeltaTime);
	
	virtual bool CreateUnit(int32 UnitTableId, const FVector& Pos = FVector::ZeroVector, const FRotator& Rot = FRotator::ZeroRotator);
	virtual void DestroyUnit();

	void SetLodScaleValues(float CullDistanceScale, float OutLineCullDistanceScale, bool bVisibleOutLine) const;
	void SetUnitPosition(const FVector& NewSpawnUnitPosition) const;
	
	FORCEINLINE void SetUnitHandle(DD_Handle _UnitHandle) { UnitHandle = _UnitHandle; }
	FORCEINLINE DD_Handle GetUnitHandle() const { return UnitHandle; }
	
	FORCEINLINE TObjectPtr<struct FResource_Unit> GetResourceUnitData() const { return ResourceUnitData; }

	// Todo 용섭 : 나중에 애님인스턴스용
	//TObjectPtr<UDD_AnimInstance> GetAnimInstance() const;
	
	FORCEINLINE TObjectPtr<ADD_CharacterBase> GetCharacterBase() const { return CharacterBase.Get(); }
	FORCEINLINE FVector GetCharacterLocation() const { return CharacterBase->GetCurrentLocation(); }

	float GetMovingSpeed() const;
	
	FDD_UnitActorTickDelegate OnActorTickDelegate;

	
protected:
	bool CreateActionStateMachine();
	void DestroyActionStateMachine();
	void AddActionState(EDD_UnitActionState State, const FName& Name, TSubclassOf<class UDD_StateBase> ClassType);
	FORCEINLINE TObjectPtr<UDD_StateBase> GetActionState(EDD_UnitActionState State) const { return ActionStateMachine->GetState(static_cast<uint8>(State)); }

	virtual void ChangeActionState(EDD_UnitActionState ActionType) const;

	TObjectPtr<UActorComponent> GetActorComponentByTag(TSubclassOf<UActorComponent> ClassType, FName TabName, bool bIncludeFromChildActors = false) const;
	
	TWeakObjectPtr<ADD_CharacterBase> CharacterBase = nullptr;
private:
	FORCEINLINE bool IsValidCharacterActor() const { return CharacterBase.IsValid(); }

	DD_Handle UnitHandle = InvalidUnitHandle;
	
	int32 ResourceUnitTableId = INDEX_NONE;
	TObjectPtr<FResource_Unit> ResourceUnitData = nullptr;
	
	UPROPERTY()
	TObjectPtr<class UDD_StateMachine> ActionStateMachine = nullptr;
};
