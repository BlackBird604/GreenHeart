// The Green Heart @Politechnika Opolska

#include "AnimalBuildingManager.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Fundamentals/FarmingGameInstance.h"
#include "Fundamentals/FarmingGameState.h"
#include "Actors/Interactables/FeedBox.h"
#include "Pawns/Animal.h"

AAnimalBuildingManager::AAnimalBuildingManager()
{
	PrimaryActorTick.bCanEverTick = false;

	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	SpawnBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpawnBox->SetBoxExtent(FVector(100.0f, 100.0f, 0.0f));
	RootComponent = SpawnBox;
}

void AAnimalBuildingManager::StartPlay()
{
	if (!AnimalClass->IsChildOf(AAnimal::StaticClass()))
	{
		AnimalClass = AAnimal::StaticClass();
	}

	FAnimalBuildingState BuildingState = GetSavedBuildingState();
	RestoreFeedBoxState(BuildingState);
	SpawnAnimals();
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
		for (int32 i = 0; i < GameState->GetCowAmount(); i++)
		{
			FVector SpawnLocation = GetRandomSpawnLocation();
			FRotator SpawnRotation = GetRandomSpawnRotation();
			AAnimal* SpawnedAnimal = GetWorld()->SpawnActor<AAnimal>(AnimalClass, SpawnLocation, SpawnRotation, SpawnInfo);
			if (SpawnedAnimal)
			{
				SpawnedAnimal->RestoreStateByID(i);
			}
		}
	}
}

FVector AAnimalBuildingManager::GetRandomSpawnLocation()
{
	FVector SpawnLocation = GetActorLocation();
	float xExtent = SpawnBox->GetScaledBoxExtent().X;
	SpawnLocation.X += FMath::RandRange(-xExtent, xExtent);
	float yExtent = SpawnBox->GetScaledBoxExtent().Y;
	SpawnLocation.Y += FMath::RandRange(-yExtent, yExtent);
	return SpawnLocation;
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
