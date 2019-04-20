// The Green Heart @Politechnika Opolska

#include "FarmingGameInstance.h"
#include "Kismet/GameplayStatics.h"

#include "Objects/FieldStateUpdater.h"

void UFarmingGameInstance::ApplyNextDay()
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

void UFarmingGameInstance::OpenLevel(FName LevelName, int32 SpawnPoint)
{
	UGameplayStatics::OpenLevel(this, LevelName, false);
}