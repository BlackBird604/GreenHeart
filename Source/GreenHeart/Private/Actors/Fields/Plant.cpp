// The Green Heart @Politechnika Opolska

#include "Plant.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Defaults/ProjectDefaults.h"

APlant::APlant()
{
	PrimaryActorTick.bCanEverTick = false;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	float TileSize = ProjectDefaults::TileSize;
	FVector BoxExtent = FVector(TileSize / 2.0f);
	CollisionBox->SetBoxExtent(BoxExtent);
	RootComponent = CollisionBox;
	PlantMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlantMesh"));
	PlantMesh->SetupAttachment(CollisionBox);
	PlantMesh->bReceivesDecals = false;
}

void APlant::BeginPlay()
{
	Super::BeginPlay();
	
}

