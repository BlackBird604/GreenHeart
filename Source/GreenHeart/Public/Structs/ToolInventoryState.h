#pragma once

#include "Structs/ToolInfo.h"
#include "ToolInventoryState.generated.h"

USTRUCT(BlueprintType)
struct FToolInventoryState
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FToolInfo> ToolInfos;
};