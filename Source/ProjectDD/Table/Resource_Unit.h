#pragma once
    
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Resource_Unit.generated.h"
    
USTRUCT()
struct FResource_Unit: public FTableRowBase
{
    GENERATED_USTRUCT_BODY()
public:
   UPROPERTY(EditAnywhere)
    int32 Index = 0;
   UPROPERTY(EditAnywhere)
    int32 Base_Path = 0;
   UPROPERTY(EditAnywhere)
    int32 Montage_Path = 0;
   UPROPERTY(EditAnywhere)
    float WalkSpeed;
   UPROPERTY(EditAnywhere)
    float AngleVelocity;
};
