// The Green Heart @Politechnika Opolska

#include "FarmerUpdater.h"

void UFarmerUpdater::ApplyNextDay(FGameStateInfo& GameStateInfo, FFarmerState& FarmerState)
{
	if (FarmerState.Energy <= HighFavigueEnergyLevel)
	{
		FarmerState.Energy = EnergyAfterHighFatigue;
		GameStateInfo.ClockInfo = ClockInfoAfterHighFatigue;
	}
	else if (FarmerState.Energy <= FavigueEnergyLevel)
	{
		FarmerState.Energy = EnergyAfterFatigue;
		GameStateInfo.ClockInfo = ClockInfoAfterFatigue;
	}
	else
	{
		FarmerState.Energy = MaxEnergy;
		GameStateInfo.ClockInfo = NormalClockInfo;
	}
}