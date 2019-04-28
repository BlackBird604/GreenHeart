// The Green Heart @Politechnika Opolska

#include "Chicken.h"
#include "Engine/World.h"

#include "Fundamentals/FarmingGameState.h"
#include "Actors/AnimalItems/Egg.h"

void AChicken::RestoreStateByID(int32 AnimalID)
{
	if (AFarmingGameState* GameState = GetWorld()->GetGameState<AFarmingGameState>())
	{
		FAnimalState SavedState = GameState->GetChickenStateByID(AnimalID);
		RestoreState(SavedState);
		if (SavedState.bHasItem)
		{
			SpawnEgg();
		}
	}
}

void AChicken::SpawnEgg()
{
	TSubclassOf<ABaseItem> ItemClass = GetItemClass();
	if (ItemClass)
	{
		FVector SpawnLocation = GetActorLocation() + FVector(0.0f, 0.0f, EggSpawnHeight);
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AEgg* SpawnedEgg = GetWorld()->SpawnActor<AEgg>(ItemClass, SpawnLocation, FRotator::ZeroRotator, SpawnInfo);
		if (SpawnedEgg)
		{
			SpawnedEgg->OnCollected.AddDynamic(this, &AChicken::OnEggCollected);
		}
	}
}

void AChicken::OnEggCollected()
{
	RemoveOwnedItem();
}

void AChicken::SaveUpdatedState()
{
	if (AFarmingGameState* GameState = GetWorld()->GetGameState<AFarmingGameState>())
	{
		FAnimalState State = GetCurrentState();
		GameState->UpdateChickenState(State);
	}
}