// The Green Heart @Politechnika Opolska

#pragma once

#include "Structs/ToolOffer.h"
#include "SupermarketInfo.generated.h"

USTRUCT(BlueprintType)
struct FSupermarketInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FToolOffer> OfferedSeeds;
};