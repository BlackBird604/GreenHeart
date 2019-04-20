// The Green Heart @Politechnika Opolska

#include "FarmingGameInstance.h"
#include "Kismet/GameplayStatics.h"

#include "Objects/FieldStateUpdater.h"
#include "Objects/ObstacleStateUpdater.h"

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
	UFieldStateUpdater* FieldUpdater = NewObject<UFieldStateUpdater>();
	FieldUpdater->ApplyNextDay(FieldGridState);
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