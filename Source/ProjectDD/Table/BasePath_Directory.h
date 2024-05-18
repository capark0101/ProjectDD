#pragma once
    
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BasePath_Directory.generated.h"
    
USTRUCT()
struct FBasePath_Directory: public FTableRowBase
{
    GENERATED_USTRUCT_BODY()
public:
   UPROPERTY(EditAnywhere)
    int32 Id = 0;
   UPROPERTY(EditAnywhere)
    FString Directory = FString();
};
