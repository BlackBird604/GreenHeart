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
	if (TileState.PlantClass)
	{
		bool bIsWatered = TileState.bIsWatered;
		ApplyNextDay(TileState.PlantState, bIsWatered, TileState.PlantClass);
		if (HasPlantMesh(TileState.PlantState, TileState.PlantClass))
		{
			TileState.bIsSeeded = false;
		}
	}

	TileState.bIsWatered = false;


}

void UFieldStateUpdater::ApplyNextDay(FPlantState& PlantState, bool bIsWatered, TSubclassOf<APlant> PlantClass)
{
	int32 GrowthIncrement = bIsWatered ? 2 : 1;
	APlant* DefaultPlant = Cast<APlant>(PlantClass->GetDefaultObject());
	if (DefaultPlant)
	{
		int32 MaxGrowthValue = DefaultPlant->GetMaxGrowthValue();
		PlantState.GrowthValue = FMath::Min(PlantState.GrowthValue + GrowthIncrement, MaxGrowthValue);
	}
}

bool UFieldStateUpdater::HasPlantMesh(FPlantState& PlantState, TSubclassOf<APlant> PlantClass)
{
	APlant* DefaultPlant = Cast<APlant>(PlantClass->GetDefaultObject());
	if (DefaultPlant)
	{
		return DefaultPlant->HasMesh(PlantState.GrowthValue);
	}
	return false;
}