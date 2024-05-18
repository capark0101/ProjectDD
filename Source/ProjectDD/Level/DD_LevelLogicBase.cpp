// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_LevelLogicBase.h"

#include "BrainComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "Utils/DD_Define.h"
#include "Utils/DD_Utility.h"

ADD_LevelLogicBase::ADD_LevelLogicBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADD_LevelLogicBase::BeginPlay()
{
	Super::BeginPlay();
}

void ADD_LevelLogicBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ADD_LevelLogicBase::IsSettedBehaviorTree()
{
	return BTAsset != nullptr;
}

bool ADD_LevelLogicBase::StopBehaviorTree()
{
	if(BTAsset && BrainComponent)
	{
		const FString Reason;
		BrainComponent->StopLogic(Reason);
		return true;
	}
	return false;
}

bool ADD_LevelLogicBase::StartBehaviorTree(bool bLoop)
{
	if(BTAsset == nullptr)
	{
		return false;
	}

	if(BlackBoardComponent == nullptr)
	{
		BlackBoardComponent = DD_NewObject<UBlackboardComponent>(this, TEXT("BlackboardComponent"));

		if(BlackBoardComponent != nullptr )
		{
			if(BlackBoardComponent->InitializeBlackboard(*BTAsset->BlackboardAsset) == false)
			{
				RemoveBehaviorTree();
			}
			else
			{
				BlackBoardComponent->RegisterComponent();

				TObjectPtr<UBehaviorTreeComponent> BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
				if(BTComponent == nullptr)
				{
					BTComponent = DD_NewObject<UBehaviorTreeComponent>(this, TEXT("BTComponent"));
					BTComponent->RegisterComponent();
					BrainComponent = BTComponent; 
				}
			}
		}
	}

	return true;
}

bool ADD_LevelLogicBase::PauseBehaviorTree()
{
	if(BrainComponent)
	{
		const TObjectPtr<UBehaviorTreeComponent> BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
		const FString Reason;
		BTComponent->PauseLogic(Reason);
		return true;
	}

	return false;
}

bool ADD_LevelLogicBase::IsPausedBehaviorTree()
{
	if(BrainComponent)
	{
		const TObjectPtr<UBehaviorTreeComponent> BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
		return BTComponent->IsPaused();
	}

	return false;
}

void ADD_LevelLogicBase::RemoveBehaviorTree()
{
	if (BTAsset != nullptr) {
		BTAsset->MarkAsGarbage();
		BTAsset = nullptr;
	}

	if (BrainComponent != nullptr) {
		BrainComponent->Cleanup();
		BrainComponent->DestroyComponent(true);
		BrainComponent = nullptr;
	}

	if (BlackBoardComponent != nullptr) {
		BlackBoardComponent->DestroyComponent(true);
		BlackBoardComponent = nullptr;
	}
}

bool ADD_LevelLogicBase::SetBehaviorTree(FString Filename)
{
	if(BTAsset != nullptr)
	{
		return false;
	}

	BTAsset = Cast<UBehaviorTree>(DD_Utility::LoadObjectFromFile(Filename));
	if(BTAsset == nullptr || BTAsset->BlackboardAsset == nullptr)
	{
		RemoveBehaviorTree();
		return false;
	}

	if(BlackBoardComponent == nullptr)
	{
		BlackBoardComponent = DD_NewObject<UBlackboardComponent>(this, TEXT("LobicBlackBoardComponent"));
		if(BlackBoardComponent != nullptr)
		{
			if(BlackBoardComponent->InitializeBlackboard(*BTAsset->BlackboardAsset) == true)
			{
				const FBlackboard::FKey SelfKey = BTAsset->BlackboardAsset->GetKeyID(FBlackboard::KeySelf);
				if(SelfKey != FBlackboard::InvalidKey)
				{
					BlackBoardComponent->SetValue<UBlackboardKeyType_Object>(SelfKey, this);
				}
			}
			else
			{
				RemoveBehaviorTree();
				return false;
			}

			BlackBoardComponent->RegisterComponent();
		}
	}

	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if(BehaviorTreeComponent == nullptr)
	{
		BehaviorTreeComponent = DD_NewObject<UBehaviorTreeComponent>(this, TEXT("LogicBehaviorTreeComponent"));
		BehaviorTreeComponent->RegisterComponent();
		BrainComponent = BehaviorTreeComponent;
	}
	else
	{
		RemoveBehaviorTree();
		return false;
	}

	return true;
}

bool ADD_LevelLogicBase::SetBehaviorTreeAsset(UBehaviorTree* _BTAsset)
{
	if (BTAsset == nullptr)
	{
		return false;
	}
	
	if (BTAsset != nullptr)
	{
		RemoveBehaviorTree();
	}

	BTAsset = _BTAsset;
	
	if (BTAsset == nullptr || BTAsset->BlackboardAsset == nullptr)
	{
		RemoveBehaviorTree();
		return false;
	}

	if (BlackBoardComponent == nullptr)
	{
		BlackBoardComponent = DD_NewObject<UBlackboardComponent>(this, TEXT("LogicBlackBoardComponent"));
		if (BlackBoardComponent != nullptr)
		{
			if (BlackBoardComponent->InitializeBlackboard(*BTAsset->BlackboardAsset))
			{
				const FBlackboard::FKey SelfKey = BTAsset->BlackboardAsset->GetKeyID(FBlackboard::KeySelf);
				if (SelfKey != FBlackboard::InvalidKey)
				{
					BlackBoardComponent->SetValue<UBlackboardKeyType_Object>(SelfKey, this);
				}
			}
			else
			{
				RemoveBehaviorTree();
				return false;
			}

			BlackBoardComponent->RegisterComponent();
		}

	}

	UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComp == nullptr)
	{
		BTComp = DD_NewObject<UBehaviorTreeComponent>(this, TEXT("LogicBrainComponent"));
		BTComp->RegisterComponent();
		BrainComponent = BTComp;
	}
	else
	{
		RemoveBehaviorTree();
		return false;
	}

	return true;
}

