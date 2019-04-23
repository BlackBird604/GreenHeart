// The Green Heart @Politechnika Opolska

#pragma once

#include "Structs/FeedBoxState.h"
#include "BarnState.generated.h"

USTRUCT(BlueprintType)
struct FBarnState
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TArray<FFeedBoxState> FeedBoxStates;
};