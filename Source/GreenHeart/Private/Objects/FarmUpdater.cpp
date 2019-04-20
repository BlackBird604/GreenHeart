// The Green Heart @Politechnika Opolska

#include "Objects/FarmUpdater.h"

#include "Structs/FieldGridState.h"
#include "Structs/FieldTileState.h"
#include "Structs/PlantState.h"

void UFarmUpdater::ApplyNextDay(FFieldGridState& GridState, TArray<FObstacleState>& ObstacleStates)
{
	TArray<FFieldTileState*> EmptyTiles;
	for (FFieldTileState& TileState : GridState.TileStates)
	{
		ApplyNextDay(TileState);
		if (!TileState.bIsBlocked && !HasPlantMesh(TileState.PlantState, TileState.PlantClass))
		{
			EmptyTiles.Add(&TileState);
		}
	}
	GenerateWeed(EmptyTiles, ObstacleStates);
}

void UFarmUpdater::ApplyNextDay(FFieldTileState& TileState)
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

void UFarmUpdater::ApplyNextDay(FPlantState& PlantState, bool bIsWatered, TSubclassOf<APlant> PlantClass)
{
	int32 GrowthIncrement = bIsWatered ? 2 : 1;
	APlant* DefaultPlant = Cast<APlant>(PlantClass->GetDefaultObject());
	if (DefaultPlant)
	{
		int32 MaxGrowthValue = DefaultPlant->GetMaxGrowthValue();
		PlantState.GrowthValue = FMath::Min(PlantState.GrowthValue + GrowthIncrement, MaxGrowthValue);
	}
}

bool UFarmUpdater::HasPlantMesh(FPlantState& PlantState, TSubclassOf<APlant> PlantClass)
{
	if (!PlantClass)
	{
		return false;
	}

	APlant* DefaultPlant = Cast<APlant>(PlantClass->GetDefaultObject());
	if (DefaultPlant)
	{
		return DefaultPlant->HasMesh(PlantState.GrowthValue);
	}
	return false;
}

void UFarmUpdater::GenerateWeed(TArray<FFieldTileState*>& EmptyTiles, TArray<FObstacleState>& ObstacleStates)
{
	int32 WeedAmount = FMath::RandRange(MinGeneratedWeeds, MaxGeneratedWeeds);
	for (int32 i = 0; i < WeedAmount && EmptyTiles.Num() > 0; i++)
	{
		int32 TileIndex = FMath::RandRange(0, EmptyTiles.Num()-1);
		FObstacleState ObstacleState;
		ObstacleState.Class = nullptr;
		ObstacleState.Location = EmptyTiles[TileIndex]->Location;
		ObstacleStates.Add(ObstacleState);
		EmptyTiles[TileIndex]->bIsTilled = false;
		EmptyTiles[TileIndex]->PlantClass = nullptr;
		EmptyTiles.RemoveAt(TileIndex);
	}
}