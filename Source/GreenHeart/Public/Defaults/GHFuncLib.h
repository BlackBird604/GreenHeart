// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GHFuncLib.generated.h"


UCLASS()
class GREENHEART_API UGHFuncLib : public UObject
{
	GENERATED_BODY()

public:
	static float XYVectorLength(const FVector& A, const FVector& B);
	
};
