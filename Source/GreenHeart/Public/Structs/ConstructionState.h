// The Green Heart @Politechnika Opolska

#pragma once

#include "Structs/LevelInfo.h"
#include "Enums/ConstructionTypes.h"
#include "ConstructionState.generated.h"

USTRUCT(BlueprintType)
struct FConstructionState
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EConstructionType ConstructionType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText Name = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText Description = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FBuildingLevelInfo> LevelInfos;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 CurrentLevel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bIsAvaliable = true;

	bool bIsUnderConstruction = false;

	int32 ConstructionTimeLeft;


	FBuildingLevelInfo GetCurrentLevelInfo()
	{
		return GetLevelInfo(CurrentLevel);
	}

	FBuildingLevelInfo GetNextLevelInfo()
	{
		return GetLevelInfo(CurrentLevel + 1);
	}

private:
	FBuildingLevelInfo GetLevelInfo(int32 Level)
	{
		if (LevelInfos.Num() > Level)
		{
			return LevelInfos[Level];
		}
		return FBuildingLevelInfo();
	}
};