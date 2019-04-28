// The Green Heart @Politechnika Opolska

#include "ConstructionUpdater.h"

void UConstructionUpdater::ApplyNextDay(TArray<FConstructionState>& ConstructionStates)
{
	for (FConstructionState& State : ConstructionStates)
	{
		State.ApplyNextDay();
	}

	bool bIsEverythingFullyUpgraded = true;
	for (FConstructionState& State : ConstructionStates)
	{
		if (State.ConstructionType != EConstructionType::Heart)
		{
			if (!State.IsMaxLevel())
			{
				bIsEverythingFullyUpgraded = false;
				break;
			}
		}
	}

	if (bIsEverythingFullyUpgraded)
	{
		for (FConstructionState& State : ConstructionStates)
		{
			if (State.ConstructionType == EConstructionType::Heart)
			{
				State.bIsAvaliable = true;
			}
		}
	}
}