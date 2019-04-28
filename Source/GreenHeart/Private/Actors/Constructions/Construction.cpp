// The Green Heart @Politechnika Opolska

#include "Construction.h"
#include "Engine/World.h"

#include "Fundamentals/FarmingGameState.h"

void AConstruction::StartPlay()
{
	if (AFarmingGameState* GameState = GetWorld()->GetGameState<AFarmingGameState>())
	{
		FConstructionState State = GameState->GetConstructionState(BuildingType);
		Initialize(State.CurrentLevel, State.bIsUnderConstruction);
	}
}