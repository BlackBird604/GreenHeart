// The Green Heart @Politechnika Opolska

#include "AnimalUpdater.h"

#include "Defaults/ProjectDefaults.h"

void UAnimalUpdater::ApplyNextDay(FGameStateInfo& GameStateInfo, FAnimalBuildingState& BarnState, FAnimalBuildingState& CoopState)
{
	UpdateAnimalBuilding(GameStateInfo.CowStates, BarnState.FeedBoxStates);
	UpdateAnimalBuilding(GameStateInfo.ChickenStates, CoopState.FeedBoxStates);
}

void UAnimalUpdater::UpdateAnimalBuilding(TArray<FAnimalState>& AnimalStates, TArray<FFeedBoxState>& FeedBoxStates)
{
	int32 BoxesFilled = 0;
	for (FFeedBoxState& FeedBoxState : FeedBoxStates)
	{
		if (FeedBoxState.bHasFeed)
		{
			BoxesFilled++;
		}
		FeedBoxState.bHasFeed = false;
	}

	for (FAnimalState& AnimalState : AnimalStates)
	{
		if (!AnimalState.bHasItem && BoxesFilled > 0)
		{
			AnimalState.bHasItem = true;
			if (AnimalState.Happiness < ProjectDefaults::MaxHappiness)
			{
				AnimalState.Happiness++;
			}
			BoxesFilled--;
		}
		else
		{
			if (AnimalState.Happiness > ProjectDefaults::MinHappiness)
			{
				AnimalState.Happiness--;
			}
		}

	}
}