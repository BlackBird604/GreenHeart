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
		int HappinessChange = 0;
		if (!AnimalState.bHasItem && BoxesFilled > 0)
		{
			AnimalState.bHasItem = true;
			HappinessChange += 1;
			BoxesFilled--;
		}
		else
		{
			if (AnimalState.bHasItem)
			{
				HappinessChange -= 1;
			}
			if (BoxesFilled <= 0)
			{
				HappinessChange -= 5;
			}
		}
		if (AnimalState.bReceivedInteraction)
		{
			HappinessChange += 2;
		}

		AnimalState.Happiness = GetClampedHappiness(AnimalState.Happiness + HappinessChange);
	}
}

int32 UAnimalUpdater::GetClampedHappiness(int32 Happiness)
{
	return FMath::Clamp(Happiness, ProjectDefaults::MinHappiness, ProjectDefaults::MaxHappiness);
}