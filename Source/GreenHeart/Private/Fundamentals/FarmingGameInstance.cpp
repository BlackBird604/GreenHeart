// The Green Heart @Politechnika Opolska

#include "FarmingGameInstance.h"
#include "Kismet/GameplayStatics.h"

#include "Objects/FarmUpdater.h"

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
}

void UFarmingGameInstance::ApplyNextDayChanges()
{
	UFarmUpdater* FieldUpdater = NewObject<UFarmUpdater>();
	FieldUpdater->ApplyNextDay(FieldGridState, ObstacleStates);
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

void UFarmingGameInstance::OpenLevel(FName LevelName, int32 SpawnPoint)
{
	UGameplayStatics::OpenLevel(this, LevelName, false);
}

void UFarmingGameInstance::StartNextDay()
{
	ApplyNextDayChanges();
	OpenLevel("Farm", 0); // TEMPORARY

}