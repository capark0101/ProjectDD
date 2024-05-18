#pragma once
    
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BasePath_Img_File.generated.h"
    
USTRUCT()
struct FBasePath_Img_File: public FTableRowBase
{
    GENERATED_USTRUCT_BODY()
public:
   UPROPERTY(EditAnywhere)
    int32 Id = 0;
   UPROPERTY(EditAnywhere)
    int32 Directory_Table_Id = 0;
   UPROPERTY(EditAnywhere)
    FString Img_File_Name = FString();
   UPROPERTY(EditAnywhere)
    bool Img_File_Local = false;
};
