// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "ResourceTypes.generated.h"

UENUM(BlueprintType)
enum class EResourceType : uint8
{
	Money,
	CowFeed,
	ChickenFeed
};