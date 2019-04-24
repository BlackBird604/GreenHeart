// The Green Heart @Politechnika Opolska

#include "CoopManager.h"

#include "Fundamentals/FarmingGameInstance.h"

FAnimalBuildingState ACoopManager::GetSavedBuildingState()
{
	if (UFarmingGameInstance* GameInstance = Cast<UFarmingGameInstance>(GetGameInstance()))
	{
		return GameInstance->GetCoopState();
	}
	return FAnimalBuildingState();
}

void ACoopManager::SaveState(const FAnimalBuildingState& CurrentBuildingState)
{
	if (UFarmingGameInstance* GameInstance = Cast<UFarmingGameInstance>(GetGameInstance()))
	{
		GameInstance->SetCoopState(CurrentBuildingState);
	}
}
