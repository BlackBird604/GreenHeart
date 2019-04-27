// The Green Heart @Politechnika Opolska

#pragma once

#include "Structs/ToolOffer.h"
#include "Structs/AnimalOffer.h"
#include "Structs/ResourceOffer.h"
#include "SupermarketInfo.generated.h"

USTRUCT(BlueprintType)
struct FSupermarketInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FToolOffer> OfferedSeeds;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FAnimalOffer> OfferedAnimals;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FResourceOffer> OfferedFeeds;
};