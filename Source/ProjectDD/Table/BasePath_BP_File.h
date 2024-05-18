#pragma once
    
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BasePath_BP_File.generated.h"
    
USTRUCT()
struct FBasePath_BP_File: public FTableRowBase
{
    GENERATED_USTRUCT_BODY()
public:
   UPROPERTY(EditAnywhere)
    int32 Id = 0;
   UPROPERTY(EditAnywhere)
    int32 Directory_Table_Id = 0;
   UPROPERTY(EditAnywhere)
    FName BP_File_Name = FName();
};
