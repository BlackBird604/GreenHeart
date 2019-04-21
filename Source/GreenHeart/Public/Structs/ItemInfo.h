// The Green Heart @Politechnika Opolska

#pragma once

#include "ItemInfo.generated.h"

USTRUCT(BlueprintType)
struct FItemInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class AActor> Class;

};