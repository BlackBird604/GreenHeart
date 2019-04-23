// The Green Heart @Politechnika Opolska

#pragma once

#include "FeedBoxState.generated.h"

USTRUCT(BlueprintType)
struct FFeedBoxState
{
	GENERATED_USTRUCT_BODY()

	int32 ID;

	bool bHasFeed;
};