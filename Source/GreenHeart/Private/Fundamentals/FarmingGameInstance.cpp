// The Green Heart @Politechnika Opolska

#include "FarmingGameInstance.h"
#include "Kismet/GameplayStatics.h"

#include "Objects/FarmUpdater.h"
#include "Objects/AnimalUpdater.h"
#include "Objects/FarmerUpdater.h"

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
	GameStateInfo = InitialGameStateInfo;

	GameStateInfo.CowStates.Add(FAnimalState()); // TEMPORARY
}

void UFarmingGameInstance::ApplyNextDayChanges()
{
	UFarmUpdater* FieldUpdater = NewObject<UFarmUpdater>();
	FieldUpdater->ApplyNextDay(FieldGridState, ObstacleStates);

	UAnimalUpdater* AnimalUpdater = NewObject<UAnimalUpdater>();
	AnimalUpdater->ApplyNextDay(GameStateInfo, BarnState);

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

void UFarmingGameInstance::SetBarnState(FBarnState NewState)
{
	BarnState = NewState;
}

FBarnState UFarmingGameInstance::GetBarnState()
{
	return BarnState;
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

