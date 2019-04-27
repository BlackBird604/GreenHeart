// The Green Heart @Politechnika Opolska

#include "FarmingGameInstance.h"
#include "Kismet/GameplayStatics.h"

#include "Objects/FarmUpdater.h"
#include "Objects/AnimalUpdater.h"
#include "Objects/FarmerUpdater.h"
#include "Actors/Tools/Tool.h"

void UFarmingGameInstance::Init()
{
	Super::Init();
	if (InitialObstacleStates)
	{
		StartNewGame(); //Temporary
	}
}

void UFarmingGameInstance::StartNewGame()
{
	for (auto ObstacleStateRow : InitialObstacleStates->GetRowMap())
	{
		FObstacleState* ObstacleState = (FObstacleState*)ObstacleStateRow.Value;
		ObstacleStates.Add(*ObstacleState);
	}
	FarmerState = InitialFarmerState;
	SetupFarmerInventory(FarmerState);
	GameStateInfo = InitialGameStateInfo;

	GameStateInfo.CowStates.Add(FAnimalState()); // TEMPORARY
	GameStateInfo.ChickenStates.Add(FAnimalState()); // TEMPORARY
	GameStateInfo.StationaryTools.SetNum(8);
	GameStateInfo.StationaryItems.SetNum(8);
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
		else
		{
			FarmerState.ToolInventoryState.ToolInfos.Add(FToolInfo());
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
	SpawnPointIndex = SpawnPoint;
	UGameplayStatics::OpenLevel(this, LevelName, false);
}

int32 UFarmingGameInstance::GetSpawnPointIndex()
{
	return SpawnPointIndex;
}

