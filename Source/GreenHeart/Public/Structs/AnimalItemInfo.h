// The Green Heart @Politechnika Opolska

#pragma once

#include "AnimalItemInfo.generated.h"

USTRUCT(BlueprintType)
struct FAnimalItemInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "100"))
	int32 RequiredHappiness = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class ABaseItem> ItemClass;
};