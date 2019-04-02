// The Green Heart @Politechnika Opolska

#include "Plant.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include"Types/CollisionTypes.h"
#include "Defaults/ProjectDefaults.h"

//Temporary
#include "Engine/World.h"
#include "TimerManager.h"

APlant::APlant()
{
	PrimaryActorTick.bCanEverTick = false;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	float TileSize = ProjectDefaults::TileSize;
	FVector BoxExtent = FVector(TileSize / 2.0f);
	CollisionBox->SetBoxExtent(BoxExtent);
	CollisionBox->SetCollisionProfileName(CollisionPresets::Plant);
	RootComponent = CollisionBox;
	PlantMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlantMesh"));
	PlantMesh->SetupAttachment(CollisionBox);
	PlantMesh->bReceivesDecals = false;
}

void APlant::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(GrowthTimer, this, &APlant::Grow, 3.0f, true, 3.0f); //Temporary
}

// TEMPORARY
void APlant::Grow()
{
	GrowthValue++;
	UStaticMesh* NewMesh = nullptr;
	for (FGrowthInfo GrowthInfo : GrowthInfos)
	{
		if (GrowthInfo.GrowthValue <= GrowthValue)
		{
			NewMesh = GrowthInfo.PlantMesh;
		}
		else
		{
			break;
		}
	}
	PlantMesh->SetStaticMesh(NewMesh);

	if (NewMesh)
	{
		CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}


