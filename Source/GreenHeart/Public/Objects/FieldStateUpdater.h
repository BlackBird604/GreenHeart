// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Structs/FieldGridState.h"
#include "FieldStateUpdater.generated.h"



UCLASS()
class GREENHEART_API UFieldStateUpdater : public UObject
{
	GENERATED_BODY()

public:
	void ApplyNextDay(FFieldGridState& GridState);

private:
	void ApplyNextDay(FFieldTileState& TileState);

	void ApplyNextDay(FPlantState& PlantState);
};