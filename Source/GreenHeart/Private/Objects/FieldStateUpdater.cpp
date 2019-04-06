// The Green Heart @Politechnika Opolska

#include "Objects/FieldStateUpdater.h"

#include "Structs/FieldGridState.h"
#include "Structs/FieldTileState.h"
#include "Structs/PlantState.h"

void UFieldStateUpdater::ApplyNextDay(FFieldGridState& GridState)
{
	for (FFieldTileState& TileState : GridState.TileStates)
	{
		ApplyNextDay(TileState);
	}
}

void UFieldStateUpdater::ApplyNextDay(FFieldTileState& TileState)
{
	ApplyNextDay(TileState.PlantState);
}

void UFieldStateUpdater::ApplyNextDay(FPlantState& PlantState)
{
	PlantState.GrowthValue++;
}