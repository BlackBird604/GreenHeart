// The Green Heart @Politechnika Opolska

#pragma once

#include "Structs/FieldTileState.h"
#include "FieldGridState.generated.h"

USTRUCT(BlueprintType)
struct FFieldGridState
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY()
		TArray<FFieldTileState> TileStates;
};