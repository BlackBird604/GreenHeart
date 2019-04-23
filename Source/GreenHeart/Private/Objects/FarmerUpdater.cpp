// The Green Heart @Politechnika Opolska

#include "FarmerUpdater.h"

void UFarmerUpdater::ApplyNextDay(FGameStateInfo& GameStateInfo, FFarmerState& FarmerState)
{
	if (FarmerState.Energy <= HighFavigueEnergyLevel)
	{
		FarmerState.Energy = EnergyAfterHighFatigue;
	}
	else if (FarmerState.Energy <= FavigueEnergyLevel)
	{
		FarmerState.Energy = EnergyAfterFatigue;
	}
	else
	{
		FarmerState.Energy = MaxEnergy;
	}
}