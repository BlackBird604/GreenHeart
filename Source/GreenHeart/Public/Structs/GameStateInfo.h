// The Green Heart @Politechnika Opolska

#pragma once

#include "Structs/AnimalState.h"
#include "GameStateInfo.generated.h"

USTRUCT(BlueprintType)
struct FGameStateInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TArray<FAnimalState> CowStates;

	UPROPERTY()
	TArray<FAnimalState> ChickenStates;
};