// The Green Heart @Politechnika Opolska

#include "ObstacleManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

#include "Actors/Obstacles/Obstacle.h"
#include "Fundamentals/FarmingGameInstance.h"

AObstacleManager::AObstacleManager()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AObstacleManager::BeginPlay()
{
	Super::BeginPlay();
	if (!WeedClass->IsChildOf(AObstacle::StaticClass()))
	{
		WeedClass = AObstacle::StaticClass();
	}
	RestoreState();
}

void AObstacleManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	SaveState();
}

void AObstacleManager::SaveState()
{
	UFarmingGameInstance* GameInstance = Cast<UFarmingGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		TArray<FObstacleState> ObstacleStates;
		for (AObstacle* Obstacle : Obstacles)
		{
			FObstacleState ObstacleState;
			ObstacleState.Class = Obstacle->GetClass();
			ObstacleState.Location = Obstacle->GetActorLocation();
			ObstacleStates.Add(ObstacleState);
		}
		GameInstance->SetObstacleStates(ObstacleStates);
	}
}

void AObstacleManager::RestoreState()
{
	UFarmingGameInstance* GameInstance = Cast<UFarmingGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		TArray<FObstacleState> ObstacleStates = GameInstance->GetObstacleStates();
		for (int32 i = 0; i < ObstacleStates.Num(); i++)
		{
			FObstacleState ObstacleState = ObstacleStates[i];
			ObstacleState.Class = ObstacleStates[i].Class ? ObstacleStates[i].Class : WeedClass;
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AObstacle* Obstacle = GetWorld()->SpawnActor<AObstacle>(ObstacleState.Class, ObstacleState.Location, FRotator(0.0f), SpawnInfo);
			Obstacle->OnObstacleDestroyed.AddDynamic(this, &AObstacleManager::RemoveObstacle);
			Obstacles.Add(Obstacle);
		}
	}
}

void AObstacleManager::RemoveObstacle(AActor* RemovedActor)
{
	AObstacle* RemovedObstacle = Cast<AObstacle>(RemovedActor);
	Obstacles.Remove(RemovedObstacle);
}