// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Structs/FarmerState.h"
#include "Structs/GameStateInfo.h"
#include "FarmerUpdater.generated.h"


UCLASS()
class GREENHEART_API UFarmerUpdater : public UObject
{
	GENERATED_BODY()
	
public:
	void ApplyNextDay(FGameStateInfo& GameStateInfo, FFarmerState& FarmerState);

private:
	const int32 FavigueEnergyLevel = 40;

	const int32 HighFavigueEnergyLevel = 20;

	const int32 MaxEnergy = 150;

	const int32 EnergyAfterFatigue = 125;

	const int32 EnergyAfterHighFatigue = 100;

};
