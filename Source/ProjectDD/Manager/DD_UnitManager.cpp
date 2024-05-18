// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_UnitManager.h"

#include "DD_BasicUtilLibrary.h"
#include "DD_UnitBase.h"
#include "DD_Utility.h"
#include "Character/DD_CharacterBase.h"

void UDD_UnitManager::Initialize()
{
}

void UDD_UnitManager::Finalize()
{
	DestroyAllUnit();
}

void UDD_UnitManager::Tick(float _DeltaTime)
{
	for(const auto& Unit : Units)
	{
		Unit.Value->Tick(_DeltaTime);
	}
}

TObjectPtr<UDD_UnitBase> UDD_UnitManager::CreateUnit(int32 UnitTableId, const TSubclassOf<UDD_UnitBase>& UnitType, const FVector& Position, const FRotator& Rotator)
{
	const TObjectPtr<UDD_UnitBase> Unit = DD_NewObject<UDD_UnitBase>(this, UnitType);
	Unit->AddToRoot();
	Unit->Initialize();
	
	if(Unit->CreateUnit(UnitTableId, Position, Rotator) == false)
	{
		return nullptr;
	}

	Unit->SetLodScaleValues(LodScale, LodScale, bOutLineModeOn);

	const DD_Handle NewUnitHandle = MakeUnitHandle(Unit);
	
	if(NewUnitHandle == InvalidUnitHandle)
	{
		return nullptr;
	}
	
	Units.Add(NewUnitHandle, Unit);
	
	return Unit;
}

void UDD_UnitManager::DestroyUnit(DD_Handle UnitHandle)
{
	if(Units.Find(UnitHandle) != nullptr)
	{
		Units[UnitHandle]->RemoveFromRoot();
		Units[UnitHandle]->Finalize();
		Units[UnitHandle]->MarkAsGarbage();
		Units[UnitHandle] = nullptr;
		Units.Remove(UnitHandle);
	}
}

void UDD_UnitManager::DestroyAllUnit()
{
	for(auto& Unit : Units)
	{
		if(Unit.Value == nullptr)
		{
			continue;
		}

		Unit.Value->RemoveFromRoot();
		Unit.Value->Finalize();
		Unit.Value->MarkAsGarbage();
		Unit.Value = nullptr;
	}
}

TObjectPtr<ADD_CharacterBase> UDD_UnitManager::CreateCharacter(const FString& BlueprintPath, const FVector& Pos, const FRotator& Rot)
{
	const TObjectPtr<ADD_CharacterBase> NewCharacter = Cast<ADD_CharacterBase>(UDD_BasicUtilLibrary::SpawnBlueprintActor(BlueprintPath, Pos, Rot));
	if(IsValid(NewCharacter))
	{
		NewCharacter->Create(DD_Utility::GetBPNameFromFullPath(BlueprintPath));
		return NewCharacter;
	}

	return nullptr;	
}

TObjectPtr<UDD_UnitBase> UDD_UnitManager::GetUnit(DD_Handle UnitHandle)
{
	const TObjectPtr<UDD_UnitBase>* pUnit = Units.Find(UnitHandle);

	return pUnit ? *pUnit : nullptr;
}

DD_Handle UDD_UnitManager::GetUnitHandle(const TObjectPtr<UDD_UnitBase>& UnitBase) const
{
	const DD_Handle* UnitHandle = Units.FindKey(UnitBase);

	return UnitHandle ? *UnitHandle : InvalidUnitHandle;
}

TObjectPtr<ADD_CharacterBase> UDD_UnitManager::GetCharacterBase(DD_Handle UnitHandle)
{
	const TObjectPtr<UDD_UnitBase>* pUnit = Units.Find(UnitHandle);

	return pUnit ? (*pUnit)->GetCharacterBase() : nullptr;
}

DD_Handle UDD_UnitManager::MakeUnitHandle(const TObjectPtr<UDD_UnitBase>& Unit) const
{
	const int32 UnitNum = Units.Num();
	const int32 NextUnitIndex = UnitNum + 1;

	if(Units.Contains(NextUnitIndex) == false)
	{
		Unit->SetUnitHandle(NextUnitIndex);
		return NextUnitIndex;
	}

	return InvalidUnitHandle;
}
