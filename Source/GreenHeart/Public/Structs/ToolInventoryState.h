#pragma once

#include "Structs/ToolInfo.h"
#include "ToolInventoryState.generated.h"

USTRUCT(BlueprintType)
struct FToolInventoryState
{
	GENERATED_USTRUCT_BODY()

	TArray<FToolInfo> ToolInfos;

	int32 Level = 1;
};