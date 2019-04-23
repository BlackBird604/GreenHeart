// The Green Heart @Politechnika Opolska

#include "FarmingGameState.h"
#include "Fundamentals/FarmingGameInstance.h"

void AFarmingGameState::BeginPlay()
{
	Super::BeginPlay();
	if (UFarmingGameInstance* GameInstance = Cast<UFarmingGameInstance>(GetGameInstance()))
	{
		FGameStateInfo SavedState = GameInstance->GetGameStateInfo();
		CowStates = SavedState.CowStates;
		ChickenStates = SavedState.ChickenStates;
	}
}

void AFarmingGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (UFarmingGameInstance* GameInstance = Cast<UFarmingGameInstance>(GetGameInstance()))
	{
		FGameStateInfo GameStateInfo = FGameStateInfo();
		GameStateInfo.CowStates = CowStates;
		GameStateInfo.ChickenStates = ChickenStates;
		GameInstance->SetGameStateInfo(GameStateInfo);
	}
}

void AFarmingGameState::AddCow()
{
	FAnimalState AnimalState = FAnimalState();
	AnimalState.ID = CowStates.Num();
	CowStates.Add(AnimalState);
}

void AFarmingGameState::AddChcicken()
{
	ChickenStates.Add(FAnimalState());
}

int32 AFarmingGameState::GetCowAmount()
{
	return CowStates.Num();
}

FAnimalState AFarmingGameState::GetCowStateByID(int32 ID)
{
	for (FAnimalState& CowState : CowStates)
	{
		if (CowState.ID == ID)
		{
			return CowState;
		}
	}

	return FAnimalState();
}

void AFarmingGameState::UpdateCowState(FAnimalState NewState)
{
	for (int32 i = 0; i < CowStates.Num(); i++)
	{
		if (CowStates[i].ID == NewState.ID)
		{
			CowStates[i] = NewState;
			break;
		}
	}

}