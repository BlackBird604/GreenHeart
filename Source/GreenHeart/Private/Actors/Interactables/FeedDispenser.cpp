// The Green Heart @Politechnika Opolska

#include "FeedDispenser.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Fundamentals/FarmingGameState.h"
#include "Types/CollisionTypes.h"
#include "Actors/Others/Feed.h"

AFeedDispenser::AFeedDispenser()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
	CollisionBox->SetCollisionProfileName(CollisionPresets::Interactable);

	DispenserMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DispenserMesh"));
	DispenserMesh->SetupAttachment(CollisionBox);
}

void AFeedDispenser::BeginPlay()
{
	Super::BeginPlay();
	if (!FeedClass->IsChildOf(AFeed::StaticClass()))
	{
		FeedClass = AFeed::StaticClass();
	}

	GameState = GetWorld()->GetGameState<AFarmingGameState>();
}

bool AFeedDispenser::CanBeCollected()
{
	if (!GameState)
	{
		return false;
	}

	int32 FeedAmount = GameState->GetResourceAmount(ResourceType);
	return FeedAmount > 0;
}

AActor* AFeedDispenser::Collect()
{
	if (!CanBeCollected())
	{
		return nullptr;
	}

	GameState->RemoveResource(ResourceType, 1);
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AActor* FeedActor = GetWorld()->SpawnActor<AActor>(FeedClass, SpawnInfo);
	return FeedActor;
}

UAnimMontage* AFeedDispenser::GetPickupMontage()
{
	return PickupMontage;
}

