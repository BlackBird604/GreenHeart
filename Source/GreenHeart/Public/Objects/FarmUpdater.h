// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Structs/FieldGridState.h"
#include "Structs/ObstacleState.h"
#include "FarmUpdater.generated.h"



UCLASS()
class GREENHEART_API UFarmUpdater : public UObject
{
	GENERATED_BODY()

public:
	void ApplyNextDay(FFieldGridState& GridState, TArray<FObstacleState>& ObstacleStates);

private:
	void ApplyNextDay(FFieldTileState& TileState);

	void ApplyNextDay(FPlantState& PlantState, bool bIsWatered, TSubclassOf<APlant> PlantClass);

	bool HasPlantMesh(FPlantState& PlantState, TSubclassOf<APlant> PlantClass);

	void GenerateWeed(TArray<FFieldTileState*>& EmptyTiles, TArray<FObstacleState>& ObstacleStates);

	int32 MinGeneratedWeeds = 3;

	int32 MaxGeneratedWeeds = 5;
};