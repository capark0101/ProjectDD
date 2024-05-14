// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_StateMachine.h"
#include "DD_StateBase.h"
#include "Utils/DD_Define.h"

void UDD_StateMachine::Create()
{
}

void UDD_StateMachine::Destroy()
{
}

void UDD_StateMachine::Tick(float DeltaTime)
{
	for(const auto& State : EntireStates)
	{
		State.Value->Tick(DeltaTime);
	}
}

void UDD_StateMachine::RegistState(int8 Index, const FName& Name, TSubclassOf<UDD_StateBase> Type, UObject* Outer)
{
	DD_CHECK (EntireStates.Find(Index) == nullptr);

	const TObjectPtr<UObject> CustomOuter = Outer != nullptr ? Outer : this;
	TObjectPtr<UDD_StateBase> State = DD_NewObject<UDD_StateBase>(CustomOuter, Type);

	State->AddToRoot();
	State->Initialize(Index, Name);
	EntireStates.Emplace(Index, State);
}

void UDD_StateMachine::UnRegistEntireStates()
{
	for (auto& State : EntireStates)
	{
		if (State.Value != nullptr)
		{
			State.Value->Finalize();
			State.Value->RemoveFromRoot();
			State.Value = nullptr;
		}
	}

	EntireStates.Empty();
}

TObjectPtr<UDD_StateBase> UDD_StateMachine::GetCurrentState()
{
	if (const TObjectPtr<UDD_StateBase>* pCurrentStateBase = EntireStates.Find(CurrentStateId))
	{
		return *pCurrentStateBase;
	}

	return nullptr;
}

void UDD_StateMachine::GetEntireStateIds(TArray<int8>& Indices) const
{
	if(EntireStates.IsEmpty())
	{
		return;
	}
	
	Indices.Empty();
	return EntireStates.GenerateKeyArray(Indices);
}

void UDD_StateMachine::SetState(int32 Index, bool bInstant)
{
	if(bInstant)
	{
		SetState_Internal(Index);
	}
	else
	{
		ChangeStateId = Index;
	}
}

TObjectPtr<UDD_StateBase> UDD_StateMachine::GetState(int32 Index) const
{
	if(EntireStates.Contains(Index))
	{
		return EntireStates[Index];
	}

	return nullptr;
}

void UDD_StateMachine::SetState_Internal(uint8 Index)
{
	PreviousStateId = CurrentStateId;

	if(const TObjectPtr<UDD_StateBase> CurrentState = GetState(CurrentStateId))
	{
		CurrentState->OnExitState();
	}

	CurrentStateId = Index;

	if(const TObjectPtr<UDD_StateBase> NextState = GetState(Index))
	{
		NextState->OnBeginState();
	}
}
