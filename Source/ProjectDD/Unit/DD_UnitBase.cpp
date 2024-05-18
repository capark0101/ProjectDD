// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_UnitBase.h"

#include "DD_TableManager.h"
#include "DD_UnitManager.h"
#include "Resource_Unit.h"

void UDD_UnitBase::Initialize()
{
}

void UDD_UnitBase::Finalize()
{
	DestroyUnit();
	OnActorTickDelegate.RemoveAll(this);
}

void UDD_UnitBase::Tick(float DeltaTime)
{
	OnActorTickDelegate.Broadcast(this);

	if(ActionStateMachine)
	{
		ActionStateMachine->Tick(DeltaTime);
	}
}

bool UDD_UnitBase::CreateUnit(int32 UnitTableId, const FVector& Pos, const FRotator& Rot)
{
	ResourceUnitTableId = UnitTableId;
	ResourceUnitData = gTableMng.GetTableRowData<FResource_Unit>(EDD_TableDataType::Resource_Unit, ResourceUnitTableId);
	if(ResourceUnitData == nullptr)
	{
		return false;
	}

	const FString BPPath = gTableMng.GetPath(EDD_TableDataType::BasePath_BP_File, ResourceUnitData->Base_Path, true);
	if(const TObjectPtr<ADD_CharacterBase> NewCharacter = gUnitMng.CreateCharacter(BPPath, Pos, Rot))
	{
		CharacterBase = NewCharacter;
		CharacterBase->SetOwnerUnitBase(this);
		
		// if(const TObjectPtr<UDD_AnimInstance> AnimInstance = GetAnimInstance())
		// {
		// 	AnimInstance->SetMoveSpeedInfo(ResourceUnitData->WalkSpeed, ResourceUnitData->RunSpeed);
		// 	AnimInstance->InitializeAnimation();
		// }
	}
	
	return true;
}

void UDD_UnitBase::DestroyUnit()
{
}

void UDD_UnitBase::SetLodScaleValues(float CullDistanceScale, float OutLineCullDistanceScale, bool bVisibleOutLine) const
{
	if(IsValidCharacterActor())
	{
		CharacterBase->SetLodScaleValues(CullDistanceScale, OutLineCullDistanceScale, bVisibleOutLine);
	}
}

void UDD_UnitBase::SetUnitPosition(const FVector& NewSpawnUnitPosition) const
{
	if(CharacterBase == nullptr)
	{
		return;
	}

	CharacterBase->SetActorLocation(NewSpawnUnitPosition);
}

bool UDD_UnitBase::CreateActionStateMachine()
{
	if(UnitHandle == InvalidUnitHandle)
	{
		return false;
	}

	if(CharacterBase == nullptr)
	{
		return false;
	}

	ActionStateMachine = DD_NewObject<UDD_StateMachine>(this, UDD_StateMachine::StaticClass());
	ActionStateMachine->AddToRoot();
	ActionStateMachine->Create();

	return true;
}

void UDD_UnitBase::DestroyActionStateMachine()
{
	if(ActionStateMachine)
	{
		ActionStateMachine->Destroy();
		ActionStateMachine->RemoveFromRoot();
		ActionStateMachine = nullptr;
	}
}

void UDD_UnitBase::AddActionState(EDD_UnitActionState State, const FName& Name, TSubclassOf<UDD_StateBase> ClassType)
{
	if(ActionStateMachine == nullptr)
	{
		return;
	}

	ActionStateMachine->RegistState(static_cast<uint8>(State), Name, ClassType, this);
}

void UDD_UnitBase::ChangeActionState(EDD_UnitActionState ActionType) const
{
	if(ActionStateMachine == nullptr)
	{
		return;
	}
	
	ActionStateMachine->SetState(static_cast<uint8>(ActionType));
}

TObjectPtr<UActorComponent> UDD_UnitBase::GetActorComponentByTag(TSubclassOf<UActorComponent> ClassType, FName TabName, bool bIncludeFromChildActors) const
{
	const TObjectPtr<ADD_CharacterBase> TargetCharacter = GetCharacterBase();
	if(TargetCharacter == nullptr)
	{
		return nullptr;
	}

	TInlineComponentArray<UActorComponent*> Components;
	TargetCharacter->GetComponents(ClassType, Components, bIncludeFromChildActors);

	for(int32 i = 0; i < Components.Num() ; ++i)
	{
		if(Components[i]->ComponentHasTag(TabName))
		{
			return Components[i];
		}
	}

	return nullptr;
}
