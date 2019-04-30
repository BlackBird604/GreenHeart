// The Green Heart @Politechnika Opolska

#pragma once

#include "FatigueInfo.generated.h"

USTRUCT(BlueprintType)
struct FFatigueInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 EnergyLevel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAnimMontage* FatigueMontage;
};