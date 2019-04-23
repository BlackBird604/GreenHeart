// The Green Heart @Politechnika Opolska

#include "FarmingGameState.h"

void AFarmingGameState::AddCow()
{
	CowStates.Add(FCowState());
}

void AFarmingGameState::AddChcicken()
{
	ChickenStates.Add(FChickenState());
}

int32 AFarmingGameState::GetCowAmount()
{
	return CowStates.Num();
}