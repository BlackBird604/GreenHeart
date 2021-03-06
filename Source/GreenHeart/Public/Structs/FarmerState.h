// The Green Heart @Politechnika Opolska

#pragma once

#include "Structs/ItemInventoryState.h"
#include "Structs/ToolInventoryState.h"
#include "FarmerState.generated.h"

USTRUCT(BlueprintType)
struct FFarmerState
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Energy;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FToolInventoryState ToolInventoryState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FItemInventoryState ItemInventoryState;

	FItemInfo ItemInHandsInfo;

	bool bHadBreakfast = true;
};