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

	void Upgrade()
	{
		if (CanUpgrade())
		{
			Level++;
			Resize();
		}
	}

	void Resize()
	{
		ItemInfos.SetNum(GetSize(Level), false);
	}

private:
	FLevelInfo GetLevelInfo(int32 CheckedLevel)
	{
		if (LevelInfos.Num() > CheckedLevel)
		{
			return LevelInfos[CheckedLevel];
		}
		return FLevelInfo();
	}

	int32 GetSize(int32 CheckedLevel)
	{
		return FMath::Pow(2, CheckedLevel + 1);
	}
};