#pragma once

#include "Structs/ItemInfo.h"
#include "Structs/LevelInfo.h"
#include "ItemInventoryState.generated.h"

USTRUCT(BlueprintType)
struct FItemInventoryState
{
	GENERATED_USTRUCT_BODY()

	TArray<FItemInfo> ItemInfos;

	int32 Level;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FLevelInfo> LevelInfos;

	bool CanUpgrade()
	{
		return LevelInfos.Num() > Level;
	}

	FLevelInfo GetCurrentLevelInfo()
	{
		return GetLevelInfo(Level);
	}

	FLevelInfo GetNextLevelInfo()
	{
		return GetLevelInfo(Level+1);
	}

private:
	FLevelInfo GetLevelInfo(int32 Level)
	{
		if (LevelInfos.Num() > Level)
		{
			return LevelInfos[Level];
		}
		return FLevelInfo();
	}
};