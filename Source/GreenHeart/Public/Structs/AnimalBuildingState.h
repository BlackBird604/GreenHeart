// The Green Heart @Politechnika Opolska

#pragma once

#include "Structs/FeedBoxState.h"
#include "AnimalBuildingState.generated.h"

USTRUCT(BlueprintType)
struct FAnimalBuildingState
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TArray<FFeedBoxState> FeedBoxStates;
};