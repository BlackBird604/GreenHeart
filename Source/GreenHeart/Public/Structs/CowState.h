// The Green Heart @Politechnika Opolska

#pragma once

#include "CowState.generated.h"

USTRUCT(BlueprintType)
struct FCowState
{
	GENERATED_USTRUCT_BODY()

	bool bHasMilk;

	int32 Happiness;
};