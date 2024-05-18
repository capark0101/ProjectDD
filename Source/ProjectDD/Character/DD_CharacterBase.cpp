// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_CharacterBase.h"


// Sets default values
ADD_CharacterBase::ADD_CharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

bool ADD_CharacterBase::Create(const FString& LabelName)
{
	SetName(LabelName);
	SetActorLabel(LabelName);

	Initialize();
	return true;
}

void ADD_CharacterBase::Destroy()
{
	CharacterName.Empty();

	Finalize();
}

void ADD_CharacterBase::Initialize()
{
	if(RootSkeletalMeshComponent)
	{
		RootSkeletalMeshComponent->Activate();

		RootSkeletalMeshComponent->bUseAsOccluder = false;
	}
}

void ADD_CharacterBase::Finalize()
{
	if(RootSkeletalMeshComponent)
	{
		RootSkeletalMeshComponent->Deactivate();
	}
	
	bInitialize = true;
}

void ADD_CharacterBase::SetLodScaleValues(float CullDistanceScale, float OutLineCullDistanceScale, bool bVisibleOutLine)
{
	LodValues.CullDistanceScale = CullDistanceScale;
	LodValues.OutLineCullDistanceScale = OutLineCullDistanceScale;
	LodValues.bVisibleOutLine = bVisibleOutLine;
}

// Called when the game starts or when spawned
void ADD_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADD_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADD_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

