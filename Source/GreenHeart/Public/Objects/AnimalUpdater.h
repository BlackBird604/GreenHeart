// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Structs/GameStateInfo.h"
#include "Structs/AnimalBuildingState.h"
#include "AnimalUpdater.generated.h"


UCLASS()
class GREENHEART_API UAnimalUpdater : public UObject
{
	GENERATED_BODY()
	
public:
	void ApplyNextDay(FGameStateInfo& GameStateInfo, FAnimalBuildingState& BarnState, FAnimalBuildingState& CoopState);

	void UpdateAnimalBuilding(TArray<FAnimalState>& CowStates, TArray<FFeedBoxState>& FeedBoxStates);

};
