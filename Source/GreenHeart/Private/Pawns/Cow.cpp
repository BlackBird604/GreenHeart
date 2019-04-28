// The Green Heart @Politechnika Opolska

#include "Cow.h"
#include "Engine/World.h"

#include "Fundamentals/FarmingGameState.h"
#include "Actors/Tools/Tool.h"

void ACow::RestoreStateByID(int32 AnimalID)
{
	if (AFarmingGameState* GameState = GetWorld()->GetGameState<AFarmingGameState>())
	{
		FAnimalState SavedState = GameState->GetCowStateByID(AnimalID);
		RestoreState(SavedState);
	}
}

void ACow::UseTool(const ATool* Instigator, int32 Strength)
{
	Super::UseTool(Instigator, Strength);
	if (Instigator)
	{
		switch (Instigator->GetType())
		{
		case EToolType::Milker:
			// TODO AddAnimation + BlockMovement
			break;
		case EToolType::Brush:
			SetReceivedInteraction();
			break;
		}
	}
}

bool ACow::CanBeCollected()
{
	return HasItem();
}

AActor* ACow::Collect()
{
	TSubclassOf<ABaseItem> ItemClass = GetItemClass();
	if (!ItemClass)
	{
		return nullptr;
	}
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AActor* MilkActor = GetWorld()->SpawnActor<AActor>(ItemClass, SpawnInfo);
	RemoveOwnedItem();

	return MilkActor;
}

void ACow::SaveUpdatedState()
{
	if (AFarmingGameState* GameState = GetWorld()->GetGameState<AFarmingGameState>())
	{
		FAnimalState State = GetCurrentState();
		GameState->UpdateCowState(State);
	}
}