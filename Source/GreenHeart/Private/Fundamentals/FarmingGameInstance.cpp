// The Green Heart @Politechnika Opolska

#include "FarmingGameInstance.h"
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
