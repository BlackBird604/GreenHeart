// The Green Heart @Politechnika Opolska

#include "FarmingGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Others/FarmerSpawnPoint.h"

#include "Fundamentals/FarmingGameInstance.h"

AActor* AFarmingGameMode::ChoosePlayerStart(AController* Player)
{
	Super::ChoosePlayerStart(Player);
	if (UFarmingGameInstance* GameInstance = Cast<UFarmingGameInstance>(GetGameInstance()))
	{
		int32 SpawnPointIndex = GameInstance->GetSpawnPointIndex();
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(this, AFarmerSpawnPoint::StaticClass(), FoundActors);
		for (AActor* FoundActor : FoundActors)
		{
			AFarmerSpawnPoint* SpawnPoint = Cast<AFarmerSpawnPoint>(FoundActor);
			int32 FoundID = SpawnPoint->GetID();
			if (SpawnPointIndex == FoundID)
			{
				return SpawnPoint;
			}
		}
	}
	return nullptr;
}