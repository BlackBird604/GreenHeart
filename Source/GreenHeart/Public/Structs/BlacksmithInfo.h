// The Green Heart @Politechnika Opolska

#pragma once

#include "Structs/ToolOffer.h"
#include "BlacksmithInfo.generated.h"

USTRUCT(BlueprintType)
struct FBlacksmithInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FToolOffer> OfferedTools;
};