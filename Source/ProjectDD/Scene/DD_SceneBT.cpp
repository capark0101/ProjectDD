// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_SceneBT.h"
#include "DD_Define.h"
#include "DD_Utility.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


ADD_SceneBT::ADD_SceneBT()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADD_SceneBT::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADD_SceneBT::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ADD_SceneBT::CreateBT(const FString& BTPath)
{
	BTAsset = Cast<UBehaviorTree>(DD_Utility::LoadObjectFromFile(BTPath));
	if(BTAsset == nullptr || BTAsset->BlackboardAsset == nullptr)
	{
		DestroyBT();
		return false;
	}

	if(BlackboardComponent == nullptr)
	{
		BlackboardComponent = NewObject<UBlackboardComponent>(this, TEXT("BlackboardComponent"));
		if(BlackboardComponent != nullptr && BlackboardComponent->InitializeBlackboard(*BTAsset->BlackboardAsset) == false)
		{
			DestroyBT();
			return false;
		}

		BlackboardComponent->RegisterComponent();
	}

	BTComponent = DD_NewObject<UBehaviorTreeComponent>(this, TEXT("BTComponent"));
	DD_CHECK(BTComponent != nullptr)

	BTComponent->RegisterComponent();
	return true;
}

void ADD_SceneBT::DestroyBT()
{
	if(BTAsset)
	{
		BTAsset = nullptr;
	}
	if(BlackboardComponent)
	{
		BlackboardComponent = nullptr;
	}
	if(BTComponent)
	{
		BTComponent = nullptr;
	}
}

void ADD_SceneBT::StartBT() const
{
	DD_CHECK(BlackboardComponent);
	DD_CHECK(BTComponent);

	BTComponent->StartTree(*BTAsset, EBTExecutionMode::SingleRun);
}

void ADD_SceneBT::StopBT() const
{
	DD_CHECK(BTComponent);

	BTComponent->StopTree(EBTStopMode::Safe);	
}

void ADD_SceneBT::PauseBT() const
{
	DD_CHECK(BTComponent);

	BTComponent->PauseLogic(TEXT("Pause"));
}

void ADD_SceneBT::ResumeBT() const
{
	DD_CHECK(BTComponent);

	BTComponent->ResumeLogic(TEXT("Resume"));
}

