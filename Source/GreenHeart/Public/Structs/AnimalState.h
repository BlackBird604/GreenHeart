// The Green Heart @Politechnika Opolska

#pragma once

#include "AnimalState.generated.h"

USTRUCT(BlueprintType)
struct FAnimalState
{
	GENERATED_USTRUCT_BODY()

	int32 ID;

	bool bHasItem = false;

	bool bReceivedInteraction = false;

	int32 Happiness = 0;
};