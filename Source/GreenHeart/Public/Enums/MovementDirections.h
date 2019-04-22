#pragma once

#include "CoreMinimal.h"
#include "MovementDirections.generated.h"

UENUM(BlueprintType)
enum class EMovementDirection : uint8
{
	Up,
	Down,
	Left,
	Right
};