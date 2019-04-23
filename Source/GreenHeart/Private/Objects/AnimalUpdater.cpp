// The Green Heart @Politechnika Opolska

#include "AnimalUpdater.h"

#include "Defaults/ProjectDefaults.h"

void UAnimalUpdater::ApplyNextDay(FGameStateInfo& GameStateInfo, FBarnState& BarnState)
{
	UpdateBarn(GameStateInfo.CowStates, BarnState.FeedBoxStates);
}

void UAnimalUpdater::UpdateBarn(TArray<FAnimalState>& CowStates, TArray<FFeedBoxState>& FeedBoxStates)
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

	for (FAnimalState& CowState : CowStates)
	{
		if (!CowState.bHasItem && BoxesFilled > 0)
		{
			CowState.bHasItem = true;
			if (CowState.Happiness < ProjectDefaults::MaxHappiness)
			{
				CowState.Happiness++;
			}
			BoxesFilled--;
		}
		else
		{
			if (CowState.Happiness > ProjectDefaults::MinHappiness)
			{
				CowState.Happiness--;
			}
		}

	}
}