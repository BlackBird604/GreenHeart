// The Green Heart @Politechnika Opolska

#include "ConstructionUpdater.h"

void UConstructionUpdater::ApplyNextDay(TArray<FConstructionState>& ConstructionStates)
{
	for (FConstructionState& State : ConstructionStates)
	{
		State.ApplyNextDay();
	}
}