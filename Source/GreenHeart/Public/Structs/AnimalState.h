// The Green Heart @Politechnika Opolska

#pragma once

#include "AnimalState.generated.h"

USTRUCT(BlueprintType)
struct FAnimalState
{
	GENERATED_USTRUCT_BODY()

	int32 ID;

	bool bHasItem;

	bool bReceivedInteraction;

	int32 Happiness;
};