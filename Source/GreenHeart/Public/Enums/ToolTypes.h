// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "ToolTypes.generated.h"

UENUM(BlueprintType)
enum class EToolType : uint8
{
	Hoe,
	WateringCan,
	Seeds,
	Hammer,
	Scythe,
	Axe,
	Milker,
	Brush
};