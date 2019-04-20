// The Green Heart @Politechnika Opolska

#pragma once

#include "Structs/PlantState.h"
#include "Actors/Fields/Plant.h"
#include "FieldTileState.generated.h"

USTRUCT(BlueprintType)
struct FFieldTileState
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TSubclassOf<APlant> PlantClass;

	UPROPERTY()
	FPlantState PlantState;

	FVector Location;

	bool bIsTilled;

	bool bIsWatered;

	bool bIsSeeded;

	bool bIsBlocked;
};