// The Green Heart @Politechnika Opolska

#include "BarnManager.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Fundamentals/FarmingGameInstance.h"
#include "Fundamentals/FarmingGameState.h"
#include "Actors/Interactables/FeedBox.h"
#include "Pawns/Animal.h"

ABarnManager::ABarnManager()
{
	PrimaryActorTick.bCanEverTick = false;

	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	SpawnBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpawnBox->SetBoxExtent(FVector(100.0f, 100.0f, 0.0f));
	RootComponent = SpawnBox;
}

void ABarnManager::BeginPlay()
{
	Super::BeginPlay();
	if (!AnimalClass->IsChildOf(AAnimal::StaticClass()))
	{
		AnimalClass = AAnimal::StaticClass();
	}

	RestoreState();
	SpawnAnimals();
}

void ABarnManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	SaveState();
}

void ABarnManager::RestoreState()
{
	if (UFarmingGameInstance* GameInstance = Cast<UFarmingGameInstance>(GetGameInstance()))
	{
		FBarnState BarnState = GameInstance->GetBarnState();
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(this, AFeedBox::StaticClass(), FoundActors);
		for (AActor* FoundActor : FoundActors)
		{
			AFeedBox* FeedBox = Cast<AFeedBox>(FoundActor);
			for (FFeedBoxState BoxState : BarnState.FeedBoxStates)
			{
				if (FeedBox->GetID() == BoxState.ID)
				{
					FeedBox->RestoreState(BoxState);
					break;
				}
			}
		}
	}
}

void ABarnManager::SpawnAnimals()
{
	if (AFarmingGameState* GameState = GetWorld()->GetGameState<AFarmingGameState>())
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		for (int32 i = 0; i < GameState->GetCowAmount(); i++)
		{
			FVector SpawnLocation = GetRandomSpawnLocation();
			FRotator SpawnRotation = GetRandomSpawnRotation();
			GetWorld()->SpawnActor<AAnimal>(AnimalClass, SpawnLocation, SpawnRotation, SpawnInfo);
		}
	}
}

FVector ABarnManager::GetRandomSpawnLocation()
{
	FVector SpawnLocation = GetActorLocation();
	float xExtent = SpawnBox->GetScaledBoxExtent().X;
	SpawnLocation.X += FMath::RandRange(-xExtent, xExtent);
	float yExtent = SpawnBox->GetScaledBoxExtent().Y;
	SpawnLocation.Y += FMath::RandRange(-yExtent, yExtent);
	return SpawnLocation;
}

FRotator ABarnManager::GetRandomSpawnRotation()
{
	FRotator SpawnRotation = FRotator::ZeroRotator;
	int32 Orientation = FMath::RandRange(0, 3);
	SpawnRotation.Yaw = 90.0f*Orientation;
	return SpawnRotation;
}

void ABarnManager::SaveState()
{
	if (UFarmingGameInstance* GameInstance = Cast<UFarmingGameInstance>(GetGameInstance()))
	{
		FBarnState BarnState = FBarnState();
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(this, AFeedBox::StaticClass(), FoundActors);
		for (AActor* FoundActor : FoundActors)
		{
			AFeedBox* FeedBox = Cast<AFeedBox>(FoundActor);
			BarnState.FeedBoxStates.Add(FeedBox->GetState());
		}
		GameInstance->SetBarnState(BarnState);
	}
}

