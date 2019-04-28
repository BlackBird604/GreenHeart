// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "ConstructionTypes.generated.h"

UENUM(BlueprintType)
enum class EConstructionType : uint8
{
	House,
	Barn,
	ChickenCoop,
	Heart
};