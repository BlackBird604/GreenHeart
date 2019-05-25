// The Green Heart @Politechnika Opolska

#include "FarmingGameInstance.h"
#include "Kismet/GameplayStatics.h"

#include "Defaults/ProjectDefaults.h"
#include "Objects/FarmUpdater.h"
#include "Objects/AnimalUpdater.h"
#include "Objects/FarmerUpdater.h"
#include "Objects/ConstructionUpdater.h"
#include "Actors/Tools/Tool.h"

void UFarmingGameInstance::Init()
{
	Super::Init();
	InitializeVariables();
}

void UFarmingGameInstance::InitializeVariables()
{
	for (auto ObstacleStateRow : InitialObstacleStates->GetRowMap())
	{
		FObstacleState* ObstacleState = (FObstacleState*)ObstacleStateRow.Value;
		ObstacleStates.Add(*ObstacleState);
	}
	FarmerState = InitialFarmerState;
	SetupFarmerInventory(FarmerState);
	GameStateInfo = InitialGameStateInfo;

	SetupStationaryInventories(GameStateInfo);
	GameStateInfo.StationaryTools.SetNum(StationaryToolInventorySize);
	GameStateInfo.StationaryItems.SetNum(StationaryItemInventorySize);
}

void UFarmingGameInstance::StartNewGame()
{
	InitializeVariables();
	OpenLevel("Farm", 6);
}

void UFarmingGameInstance::SetupFarmerInventory(FFarmerState& FarmerState)
{
	for (TSubclassOf<ATool> ToolClass : InitialToolClasses)
	{
		if (ToolClass)
		{
			ATool* DefaultTool = Cast<ATool>(ToolClass->GetDefaultObject());
			FarmerState.ToolInventoryState.ToolInfos.Add(DefaultTool->GetToolInfo());
		}
	}
}

void UFarmingGameInstance::SetupStationaryInventories(FGameStateInfo& GameState)
{
	for (TSubclassOf<ATool> ToolClass : InitialStationaryToolClasses)
	{
		if (ToolClass)
		{
			ATool* DefaultTool = Cast<ATool>(ToolClass->GetDefaultObject());
			GameState.StationaryTools.Add(DefaultTool->GetToolInfo());
		}
	}
}

void UFarmingGameInstance::ApplyNextDayChanges()
{
	UFarmUpdater* FieldUpdater = NewObject<UFarmUpdater>();
	FieldUpdater->ApplyNextDay(FieldGridState, ObstacleStates);

	UAnimalUpdater* AnimalUpdater = NewObject<UAnimalUpdater>();
	AnimalUpdater->ApplyNextDay(GameStateInfo, BarnState, CoopState);

	UFarmerUpdater* FarmerUpdater = NewObject<UFarmerUpdater>();
	FarmerUpdater->ApplyNextDay(GameStateInfo, FarmerState);

	UConstructionUpdater* ConstructionUpdater = NewObject<UConstructionUpdater>();
	ConstructionUpdater->ApplyNextDay(GameStateInfo.ConstructionStates);
}

void UFarmingGameInstance::SetGridState(FFieldGridState NewState)
{
	FieldGridState = NewState;
}

FFieldGridState UFarmingGameInstance::GetGridState()
{
	return FieldGridState;
}

void UFarmingGameInstance::SetObstacleStates(TArray<FObstacleState> NewObstacleStates)
{
	ObstacleStates = NewObstacleStates;
}

TArray<FObstacleState> UFarmingGameInstance::GetObstacleStates()
{
	return ObstacleStates;
}

void UFarmingGameInstance::SetFarmerState(FFarmerState NewState)
{
	FarmerState = NewState;
}

FFarmerState UFarmingGameInstance::GetFarmerState()
{
	return FarmerState;
}

void UFarmingGameInstance::SetBarnState(FAnimalBuildingState NewState)
{
	BarnState = NewState;
}

FAnimalBuildingState UFarmingGameInstance::GetBarnState()
{
	return BarnState;
}

void UFarmingGameInstance::SetCoopState(FAnimalBuildingState NewState)
{
	CoopState = NewState;
}

FAnimalBuildingState UFarmingGameInstance::GetCoopState()
{
	return CoopState;
}

void UFarmingGameInstance::SetGameStateInfo(FGameStateInfo NewState)
{
	GameStateInfo = NewState;
}

FGameStateInfo UFarmingGameInstance::GetGameStateInfo()
{
	return GameStateInfo;
}

void UFarmingGameInstance::StartNextDay()
{
	OpenLevel("NextDayLevel", 0);
}

void UFarmingGameInstance::OpenLevel(FName LevelName, int32 SpawnPoint)
{
	FName AdjustedLevelName = GetLevelNameWithSuffix(LevelName);
	SpawnPointIndex = SpawnPoint;
	UGameplayStatics::OpenLevel(this, AdjustedLevelName, false);
}

FName UFarmingGameInstance::GetLevelNameWithSuffix(FName LevelName)
{
	if (LevelName == "House")
	{
		return GetLevelNameWithSuffix("House", EConstructionType::House);
	}

	if (LevelName == "Barn")
	{
		return GetLevelNameWithSuffix("Barn", EConstructionType::Barn);
	}

	if (LevelName == "Coop")
	{
		return GetLevelNameWithSuffix("Coop", EConstructionType::ChickenCoop);
	}
	return LevelName;
}

FName UFarmingGameInstance::GetLevelNameWithSuffix(FName Prefix, EConstructionType ConstructionType)
{
	TArray<FConstructionState> ConstructionStates = GameStateInfo.ConstructionStates;
	for (FConstructionState State : ConstructionStates)
	{
		if (State.ConstructionType == ConstructionType)
		{
			FString NewLevelName = Prefix.ToString() + FString::FromInt(State.CurrentLevel);
			return FName(*NewLevelName);
		}
	}
	return Prefix;
}

int32 UFarmingGameInstance::GetSpawnPointIndex()
{
	return SpawnPointIndex;
}

void UFarmingGameInstance::SetBackgroundMusicTime(float NewTime)
{
	BackgroundMusicTime = NewTime;
}

float UFarmingGameInstance::GetBackgroundMusicTime()
{
	return BackgroundMusicTime;
}