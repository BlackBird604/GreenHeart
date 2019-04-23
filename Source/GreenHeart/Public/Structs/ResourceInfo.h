// The Green Heart @Politechnika Opolska

#pragma once

#include "ResourceInfo.generated.h"

USTRUCT(BlueprintType)
struct FResourceInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Amount;
};