// The Green Heart @Politechnika Opolska

#include "Cow.h"
#include "Engine/World.h"

#include "Fundamentals/FarmingGameState.h"

void ACow::RestoreStateByID(int32 AnimalID)
{
	if (AFarmingGameState* GameState = GetWorld()->GetGameState<AFarmingGameState>())
	{
		FAnimalState SavedState = GameState->GetCowStateByID(AnimalID);
		RestoreState(SavedState);
	}
}

void ACow::SaveUpdatedState()
{
	if (AFarmingGameState* GameState = GetWorld()->GetGameState<AFarmingGameState>())
	{
		FAnimalState State = GetCurrentState();
		GameState->UpdateCowState(State);
	}
}