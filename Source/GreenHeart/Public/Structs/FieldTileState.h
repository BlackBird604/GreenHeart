// The Green Heart @Politechnika Opolska

#pragma once

#include "Structs/PlantState.h"
#include "FieldTileState.generated.h"

USTRUCT(BlueprintType)
struct FFieldTileState
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TSubclassOf<class APlant> PlantClass;

	UPROPERTY()
	FPlantState PlantState;

	bool bIsTilled;

	bool bIsWatered;

	bool bIsSeeded;
};