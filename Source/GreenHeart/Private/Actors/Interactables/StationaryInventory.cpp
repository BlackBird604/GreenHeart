// The Green Heart @Politechnika Opolska

#include "StationaryInventory.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Types/CollisionTypes.h"
#include "Fundamentals/FarmingGameMode.h"

AStationaryInventory::AStationaryInventory()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
	CollisionBox->SetCollisionProfileName(CollisionPresets::Interactable);

	InventoryMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InventoryMesh"));
	InventoryMesh->SetupAttachment(CollisionBox);
}

void AStationaryInventory::BeginPlay()
{
	Super::BeginPlay();
	
}

void AStationaryInventory::Interact()
{
	if (AFarmingGameMode* GameMode = GetWorld()->GetAuthGameMode<AFarmingGameMode>())
	{
		GameMode->OpenStationaryInventory(InventoryType);
	}
}

