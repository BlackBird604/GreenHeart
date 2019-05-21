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
		return LevelInfos.Num() > Level+1;
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

	void UpdateCurrentTool()
	{
		if (ToolInfos.Num() > 0)
		{
			FToolInfo Tool = GetCurrentTool();
			Tool.Upgrade();
			ToolInfos[0] = Tool;
		}
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
		ToolInfos.SetNum(GetSize(Level), false);
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
		return FMath::Pow(2, CheckedLevel + 1) + 1;
	}
};