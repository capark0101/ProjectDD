// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_StateBase.h"
#include "DD_StateMachine.h"

void UDD_StateBase::Initialize(uint8 Index, const FName& Name)
{
	StateIndex = Index;
	StateName = Name;
}

void UDD_StateBase::Finalize()
{
}

void UDD_StateBase::Tick(float DeltaTime)
{
}

void UDD_StateBase::OnBeginState()
{
	Begin();
}

void UDD_StateBase::OnExitState()
{
	Exit();
}

TObjectPtr<UDD_StateMachine> UDD_StateBase::GetStateMachine() const
{
	return Cast<UDD_StateMachine>(GetOuter());
}
