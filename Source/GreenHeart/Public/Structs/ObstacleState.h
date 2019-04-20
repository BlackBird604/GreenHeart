// The Green Heart @Politechnika Opolska

#pragma once

#include "Engine/DataTable.h"
#include "Actors/Obstacles/Obstacle.h"
#include "ObstacleState.generated.h"

USTRUCT(BlueprintType)
struct FObstacleState : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AObstacle> Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location;

};