// The Green Heart @Politechnika Opolska

#include "Chicken.h"
#include "Engine/World.h"

#include "Fundamentals/FarmingGameState.h"

void AChicken::RestoreStateByID(int32 AnimalID)
{
	if (AFarmingGameState* GameState = GetWorld()->GetGameState<AFarmingGameState>())
	{
		FAnimalState SavedState = GameState->GetChickenStateByID(AnimalID);
		RestoreState(SavedState);
	}
}

void AChicken::SaveUpdatedState()
{
	if (AFarmingGameState* GameState = GetWorld()->GetGameState<AFarmingGameState>())
	{
		FAnimalState State = GetCurrentState();
		GameState->UpdateChickenState(State);
	}
}