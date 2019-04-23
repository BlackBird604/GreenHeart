#pragma once

#include "Structs/ItemInfo.h"
#include "ItemInventoryState.generated.h"

USTRUCT(BlueprintType)
struct FItemInventoryState
{
	GENERATED_USTRUCT_BODY()

	int32 Level = 1;

	TArray<FItemInfo> ItemInfos;
};