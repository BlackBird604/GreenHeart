// The Green Heart @Politechnika Opolska

#include "Plant.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Types/CollisionTypes.h"
#include "Defaults/ProjectDefaults.h"
#include "Actors/Fields/Crop.h"

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
}

void APlant::UpdateMesh()
{
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

void APlant::UseTool(const ATool* Instigator)
{
	UE_LOG(LogTemp, Warning, TEXT("PLANT AFFECTED!"));
}

bool APlant::CanBeCollected()
{
	return GrowthValue >= GetMaxGrowthValue();
}

AActor* APlant::Collect()
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AActor* CropActor = GetWorld()->SpawnActor<AActor>(CropClass, SpawnInfo);

	OnDepleted.Broadcast();
	Destroy();
	return CropActor;
}


FPlantState APlant::GetState()
{
	FPlantState State;
	State.GrowthValue = GrowthValue;
	return State;
}

void APlant::RestoreState(const FPlantState& PlantState)
{
	GrowthValue = PlantState.GrowthValue;
	UpdateMesh();
}

int32 APlant::GetMaxGrowthValue()
{
	int32 MaxValue = 0;
	for (FGrowthInfo GrowthInfo : GrowthInfos)
	{
		MaxValue = FMath::Max(MaxValue, GrowthInfo.GrowthValue);
	}
	return MaxValue;
}

bool APlant::HasMesh(int32 CheckedValue)
{
	for (FGrowthInfo GrowthInfo : GrowthInfos)
	{
		if (CheckedValue >= GrowthInfo.GrowthValue)
		{
			return true;
		}
	}
	return false;
}
