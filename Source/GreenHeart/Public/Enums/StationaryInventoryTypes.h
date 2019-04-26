// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "StationaryInventoryTypes.generated.h"

UENUM(BlueprintType)
enum class EStationaryInventoryType : uint8
{
	Tool,
	Item
};