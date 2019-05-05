// The Green Heart @Politechnika Opolska

#include "AnimalBuildingManager.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Fundamentals/FarmingGameInstance.h"
#include "Fundamentals/FarmingGameState.h"
#include "Actors/Interactables/FeedBox.h"
#include "Actors/Others/AnimalSpawnPoint.h"
#include "Pawns/Animal.h"

AAnimalBuildingManager::AAnimalBuildingManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AAnimalBuildingManager::StartPlay()
{
	if (!AnimalClass->IsChildOf(AAnimal::StaticClass()))
	{
		AnimalClass = AAnimal::StaticClass();
	}

	FAnimalBuildingState BuildingState = GetSavedBuildingState();
	RestoreFeedBoxState(BuildingState);
	InitializeSpawnPoints();
	SpawnAnimals();
}

void AAnimalBuildingManager::InitializeSpawnPoints()
{
	SpawnPoints.Empty();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(this, AAnimalSpawnPoint::StaticClass(), FoundActors);
	for (AActor* FoundActor : FoundActors)
	{
		if (AAnimalSpawnPoint* SpawnPoint = Cast<AAnimalSpawnPoint>(FoundActor))
		{
			SpawnPoints.Add(SpawnPoint);
		}
	}
}

void AAnimalBuildingManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	FAnimalBuildingState BuildingState = GetCurrentBuildingState();
	SaveState(BuildingState);
}

void AAnimalBuildingManager::RestoreFeedBoxState(const FAnimalBuildingState& BuildingState)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(this, AFeedBox::StaticClass(), FoundActors);
	for (AActor* FoundActor : FoundActors)
	{
		AFeedBox* FeedBox = Cast<AFeedBox>(FoundActor);
		for (FFeedBoxState BoxState : BuildingState.FeedBoxStates)
		{
			if (FeedBox->GetID() == BoxState.ID)
			{
				FeedBox->RestoreState(BoxState);
				break;
			}
		}
	}
}

void AAnimalBuildingManager::SpawnAnimals()
{
	if (AFarmingGameState* GameState = GetWorld()->GetGameState<AFarmingGameState>())
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		int32 SpawnAmount = 0;
		switch (AnimalType)
		{
		case EAnimalType::Cow:
			SpawnAmount = GameState->GetCowAmount();
			break;
		case EAnimalType::Chicken:
			SpawnAmount = GameState->GetChickenAmount();
			break;
		}

		for (int32 i = 0; i < SpawnAmount && SpawnPoints.Num() > 0; i++)
		{
			int32 SpawnPointIndex = FMath::RandRange(0, SpawnPoints.Num() - 1);
			AAnimalSpawnPoint* SpawnPoint = SpawnPoints[SpawnPointIndex];
			SpawnPoints.RemoveAt(SpawnPointIndex);
			FVector SpawnLocation = SpawnPoint->GetActorLocation();
			FRotator SpawnRotation = GetRandomSpawnRotation();
			AAnimal* SpawnedAnimal = GetWorld()->SpawnActor<AAnimal>(AnimalClass, SpawnLocation, SpawnRotation, SpawnInfo);
			if (SpawnedAnimal)
			{
				SpawnedAnimal->RestoreStateByID(i);
			}
		}
	}
}

FRotator AAnimalBuildingManager::GetRandomSpawnRotation()
{
	FRotator SpawnRotation = FRotator::ZeroRotator;
	int32 Orientation = FMath::RandRange(0, 3);
	SpawnRotation.Yaw = 90.0f*Orientation;
	return SpawnRotation;
}

FAnimalBuildingState AAnimalBuildingManager::GetCurrentBuildingState()
{
	FAnimalBuildingState BuildingState;
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(this, AFeedBox::StaticClass(), FoundActors);
	for (AActor* FoundActor : FoundActors)
	{
		AFeedBox* FeedBox = Cast<AFeedBox>(FoundActor);
		BuildingState.FeedBoxStates.Add(FeedBox->GetState());
	}
	return BuildingState;
}
