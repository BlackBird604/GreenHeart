// The Green Heart @Politechnika Opolska

#include "FieldTile.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Engine/World.h"
#include "Materials/MaterialInstance.h"

#include "Actors/Fields/Plant.h"

AFieldTile::AFieldTile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
	FVector BoxExtent = FVector(50, 50, 1);
	CollisionBox->SetBoxExtent(BoxExtent);

	Decal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
	Decal->DecalSize = FVector(50, 50, 50);
	Decal->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	Decal->SetupAttachment(CollisionBox);
}

void AFieldTile::BeginPlay()
{
	Super::BeginPlay();
}

void AFieldTile::SpawnPlant()
{
	if (PlantClass != nullptr)
	{
		FActorSpawnParameters SpawnInfo;
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = GetActorRotation();
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		PlantActor = GetWorld()->SpawnActor<APlant>(PlantClass, SpawnLocation, SpawnRotation, SpawnInfo);
	}
}

void AFieldTile::UseTool(const ATool* Instigator)
{
	if (!Instigator)
	{
		return;
	}
}

