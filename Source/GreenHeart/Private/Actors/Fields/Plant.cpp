// The Green Heart @Politechnika Opolska

#include "Plant.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Types/CollisionTypes.h"
#include "Defaults/ProjectDefaults.h"
#include "Actors/Fields/Crop.h"
#include "Actors/Tools/Tool.h"
#include "Actors/Others/DestroyActor.h"

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

void APlant::UseTool(const ATool* Instigator, int32 Strength)
{
	if (!Instigator)
	{
		return;
	}

	if (Instigator->GetType() == EToolType::Scythe)
	{
		HandleDestroy();
	}
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

	NumberOfCollections--;
	if (NumberOfCollections <= 0)
	{
		HandleDestroy();
	}
	else
	{
		GrowthValue = GrowthValueAfterCollecting;
		UpdateMesh();
	}

	return CropActor;
}

UAnimMontage* APlant::GetPickupMontage()
{
	return PickupMontage;
}


FPlantState APlant::GetState()
{
	FPlantState State;
	State.GrowthValue = GrowthValue;
	State.CollectionsLeft = NumberOfCollections;
	return State;
}

void APlant::RestoreState(const FPlantState& PlantState)
{
	GrowthValue = PlantState.GrowthValue;
	NumberOfCollections = PlantState.CollectionsLeft;
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

void APlant::HandleDestroy()
{
	OnDepleted.Broadcast();
	SpawnDestroyActor();
	Destroy();
}

void APlant::SpawnDestroyActor()
{
	FActorSpawnParameters SpawnInfo;
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<ADestroyActor>(DestroyActorClass, SpawnLocation, SpawnRotation, SpawnInfo);
}