#pragma once
    
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Resource_Widget.generated.h"
    
USTRUCT()
struct FResource_Widget: public FTableRowBase
{
    GENERATED_USTRUCT_BODY()
public:
   UPROPERTY(EditAnywhere)
    int32 Index = 0;
   UPROPERTY(EditAnywhere)
    FName TypeName = FName();
   UPROPERTY(EditAnywhere)
    int32 zOrder = 0;
   UPROPERTY(EditAnywhere)
    int32 Path_File = 0;
   UPROPERTY(EditAnywhere)
    bool NotRender3D = false;
   UPROPERTY(EditAnywhere)
    int32 ExclusiveGroup = 0;
};
