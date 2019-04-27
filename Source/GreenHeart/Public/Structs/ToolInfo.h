// The Green Heart @Politechnika Opolska

#pragma once

#include "Templates/SubclassOf.h"
#include "Structs/LevelInfo.h"
#include "ToolInfo.generated.h"

USTRUCT(BlueprintType)
struct FToolInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText Name = FText();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText Description = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class ATool> Class = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FLevelInfo> LevelInfos;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 CurrentLevel = 0;

	bool CanUpgrade()
	{
		return LevelInfos.Num() > CurrentLevel + 1;
	}

	void Upgrade()
	{
		if (CanUpgrade())
		{
			CurrentLevel++;
		}
	}

	FLevelInfo GetCurrentLevelInfo()
	{
		return GetLevelInfo(CurrentLevel);
	}

	FLevelInfo GetNextLevelInfo()
	{
		return GetLevelInfo(CurrentLevel + 1);
	}

	FLevelInfo GetFirstLevelInfo()
	{
		return GetLevelInfo(0);
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