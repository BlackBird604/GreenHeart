// The Green Heart @Politechnika Opolska

#include "HouseBuilderStand.h"
#include "Engine/World.h"

#include "Fundamentals/FarmingGameMode.h"

void AHouseBuilderStand::StartPlay()
{
	// TODO Initialize Merchant
}

void AHouseBuilderStand::Interact()
{
	if (AFarmingGameMode* GameMode = GetWorld()->GetAuthGameMode<AFarmingGameMode>())
	{
		if (GameMode->IsConstructionInProgress())
		{
			return;
		}
	}

	Super::Interact();
}