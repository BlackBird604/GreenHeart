// The Green Heart @Politechnika Opolska

#include "BarnManager.h"

#include "Fundamentals/FarmingGameInstance.h"

FAnimalBuildingState ABarnManager::GetSavedBuildingState()
{
	if (UFarmingGameInstance* GameInstance = Cast<UFarmingGameInstance>(GetGameInstance()))
	{
		return GameInstance->GetBarnState();
	}
	return FAnimalBuildingState();
}

void ABarnManager::SaveState(const FAnimalBuildingState& CurrentBuildingState)
{
	if (UFarmingGameInstance* GameInstance = Cast<UFarmingGameInstance>(GetGameInstance()))
	{
		GameInstance->SetBarnState(CurrentBuildingState);
	}
}