// The Green Heart @Politechnika Opolska

#pragma once

#include "ToolOffer.generated.h"

USTRUCT(BlueprintType)
struct FToolOffer
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class ATool> OfferedClass = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Price;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bIsAvaliable = true;
};