// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DD_Define.h"
#include "GameFramework/Character.h"
#include "DD_CharacterBase.generated.h"

UCLASS()
class PROJECTDD_API ADD_CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ADD_CharacterBase();\

	bool Create(const FString& LabelName);
	void Destroy();

	void Initialize();
	void Finalize();

	void SetLodScaleValues(float CullDistanceScale, float OutLineCullDistanceScale, bool bVisibleOutLine);
	
	FORCEINLINE FVector GetCurrentLocation() const { return GetActorLocation(); }
	FORCEINLINE FRotator GetCurrentRotator() const { return GetActorRotation(); }
	
	FORCEINLINE void SetOwnerUnitBase(const TObjectPtr<class UObject>& _UnitBase) { OwnerUnitBase = _UnitBase; } 

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	FORCEINLINE void SetName(const FString& Name) { CharacterName = Name; }
	
	UPROPERTY(Category = ACY_CharacterBase, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString CharacterName = FString();
	
	UPROPERTY(Category = ACY_CharacterBase, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> RootSkeletalMeshComponent = nullptr;
	
	UPROPERTY(Category = ACY_CharacterBase, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FDD_CharacterLodValues LodValues = FDD_CharacterLodValues();
	
	TWeakObjectPtr<UObject> OwnerUnitBase = nullptr;
	
	bool bInitialize = false;
};