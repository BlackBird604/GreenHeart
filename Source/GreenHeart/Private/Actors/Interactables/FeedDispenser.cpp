// The Green Heart @Politechnika Opolska

#include "FeedDispenser.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

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
	
}

bool AFeedDispenser::CanBeCollected()
{
	return FeedAmount > 0;
}

AActor* AFeedDispenser::Collect()
{
	if (!CanBeCollected())
	{
		return nullptr;
	}

	FeedAmount--;
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AActor* FeedActor = GetWorld()->SpawnActor<AActor>(FeedClass, SpawnInfo);
	return FeedActor;
}

