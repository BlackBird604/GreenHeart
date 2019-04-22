#pragma once

#include "Structs/ItemInfo.h"
#include "ItemInventoryState.generated.h"

USTRUCT(BlueprintType)
struct FItemInventoryState
{
	GENERATED_USTRUCT_BODY()

	TArray<FItemInfo> ItemInfos;
};