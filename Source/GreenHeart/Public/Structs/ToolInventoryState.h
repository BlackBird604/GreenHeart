#pragma once

#include "Structs/ToolInfo.h"
#include "ToolInventoryState.generated.h"

USTRUCT(BlueprintType)
struct FToolInventoryState
{
	GENERATED_USTRUCT_BODY()

	TArray<FToolInfo> ToolInfos;

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
		return GetLevelInfo(Level + 1);
	}

	FToolInfo GetCurrentTool()
	{
		if (ToolInfos.Num() > 0)
		{
			return ToolInfos[0];
		}
		return FToolInfo();
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