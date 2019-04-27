// The Green Heart @Politechnika Opolska

#pragma once

#include "LevelInfo.generated.h"

USTRUCT(BlueprintType)
struct FLevelInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UTexture2D* Thumbnail = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Cost;
};