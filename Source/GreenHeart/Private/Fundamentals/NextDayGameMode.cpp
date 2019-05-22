// The Green Heart @Politechnika Opolska

#include "NextDayGameMode.h"

#include "Fundamentals/FarmingGameInstance.h"

void ANextDayGameMode::BeginPlay()
{
	if (UFarmingGameInstance* GameInstance = Cast<UFarmingGameInstance>(GetGameInstance()))
	{
		GameInstance->ApplyNextDayChanges();
		GameInstance->OpenLevel("House", 1);
	}
}