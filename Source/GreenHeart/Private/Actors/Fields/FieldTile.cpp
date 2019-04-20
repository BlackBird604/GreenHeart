// The Green Heart @Politechnika Opolska

#include "FieldTile.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Engine/World.h"
#include "Materials/MaterialInstance.h"

#include "Defaults/ProjectDefaults.h"
#include "Types/CollisionTypes.h"
#include "Actors/Fields/Plant.h"
#include "Actors/Tools/Seeds.h"

AFieldTile::AFieldTile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
	float TileSize = ProjectDefaults::TileSize;
	FVector BoxExtent = FVector(TileSize/2.0f, TileSize/2.0f, 1.0f);
	CollisionBox->SetBoxExtent(BoxExtent);

	Decal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
	Decal->DecalSize = FVector(TileSize/2.0f);
	Decal->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	Decal->SetupAttachment(CollisionBox);
	Decal->SetHiddenInGame(true);

	CollisionBox->SetCollisionProfileName(CollisionPresets::Field);
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
		if (PlantActor)
		{
			PlantActor->OnDepleted.AddDynamic(this, &AFieldTile::ClearPlant);
		}
	}
}

void AFieldTile::UseTool(const ATool* Instigator, int32 Strength)
{
	if (!Instigator || isBlocked())
	{
		return;
	}

	switch (Instigator->GetType())
	{
	case EToolType::Hoe:
		if (!bIsTilled)
		{
			bIsTilled = true;
		}
		break;

	case EToolType::WateringCan:
		if (bIsTilled)
		{
			bIsWatered = true;
			Decal->SetDecalMaterial(Wet);
		}
		break;

	case EToolType::Seeds:
		if (bIsTilled)
		{
			if (const ASeeds* Seeds = Cast<ASeeds>(Instigator))
			{
				if (!PlantClass)
				{
					PlantClass = Seeds->GetPlantClass();
					SpawnPlant();
					bIsSeeded = true;
				}
			}
		}
		break;
	}
	UpdateDecalMaterial();
}

void AFieldTile::UpdateDecalMaterial()
{
	if (!bIsTilled)
	{
		Decal->SetDecalMaterial(nullptr);
		Decal->SetHiddenInGame(true);
		return;
	}

	Decal->SetHiddenInGame(false);
	if (!bIsWatered && !bIsSeeded)
	{
		Decal->SetDecalMaterial(Dry);
	}
	else if (bIsWatered && !bIsSeeded)
	{
		Decal->SetDecalMaterial(Wet);
	}
	else if (!bIsWatered && bIsSeeded)
	{
		Decal->SetDecalMaterial(DrySeeded);
	}
	else
	{
		Decal->SetDecalMaterial(WetSeeded);
	}
}

FFieldTileState AFieldTile::GetState()
{
	FFieldTileState State;
	State.bIsTilled = bIsTilled;
	State.bIsWatered = bIsWatered;
	State.bIsSeeded = bIsSeeded;
	State.PlantClass = PlantClass;
	if (PlantActor)
	{
		State.PlantState = PlantActor->GetState();
	}
	State.bIsBlocked = isBlocked();
	State.Location = GetActorLocation();
	return State;
}

void AFieldTile::RestoreState(const FFieldTileState& TileState)
{
	bIsTilled = TileState.bIsTilled;
	bIsWatered = TileState.bIsWatered;
	bIsSeeded = TileState.bIsSeeded;
	PlantClass = TileState.PlantClass;
	SpawnPlant();
	if (PlantActor)
	{
		PlantActor->RestoreState(TileState.PlantState);
	}
	UpdateDecalMaterial();
}

void AFieldTile::ClearPlant()
{
	PlantClass = nullptr;
}

bool AFieldTile::isBlocked()
{
	float TraceLength = 100.0f;
	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = TraceStart + FVector(0.0f, 0.0f, TraceLength);

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_ObstacleTrace);

	return HitResult.bBlockingHit;
}
