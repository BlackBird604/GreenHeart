// The Green Heart @Politechnika Opolska

#include "FarmingGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Managers/ManagerBase.h"
#include "Actors/Others/FarmerSpawnPoint.h"

#include "Fundamentals/FarmingGameInstance.h"

void AFarmingGameMode::StartPlay()
{
	Super::StartPlay();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(this, AManagerBase::StaticClass(), FoundActors);
	for (AActor* FoundActor : FoundActors)
	{
		AManagerBase* Manager = Cast<AManagerBase>(FoundActor);
		Manager->StartPlay();
	}
}

AActor* AFarmingGameMode::ChoosePlayerStart(AController* Player)
{
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
