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

	FItemInventoryState ItemInventoryState;

	TSubclassOf<class AActor> ItemInHandsClass;
};