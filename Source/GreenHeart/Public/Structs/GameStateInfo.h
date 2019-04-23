// The Green Heart @Politechnika Opolska

#pragma once

#include "Enums/ResourceTypes.h"
#include "Structs/ResourceInfo.h"
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<EResourceType, FResourceInfo> ResourceInfos;
};