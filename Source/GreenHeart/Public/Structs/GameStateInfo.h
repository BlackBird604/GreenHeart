// The Green Heart @Politechnika Opolska

#pragma once

#include "Enums/ResourceTypes.h"
#include "Structs/ClockInfo.h"
#include "Structs/ResourceInfo.h"
#include "Structs/AnimalState.h"
#include "Structs/ToolInfo.h"
#include "Structs/ItemInfo.h"
#include "Structs/BlacksmithInfo.h"
#include "Structs/SupermarketInfo.h"
#include "Structs/ConstructionState.h"
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FClockInfo ClockInfo;

	UPROPERTY()
	TArray<FToolInfo> StationaryTools;

	UPROPERTY()
	TArray<FItemInfo> StationaryItems;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FBlacksmithInfo BlacksmithInfo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FSupermarketInfo SupermarketInfo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FConstructionState> ConstructionStates;
};