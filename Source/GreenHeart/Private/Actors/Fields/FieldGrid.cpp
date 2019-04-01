// The Green Heart @Politechnika Opolska

#include "FieldGrid.h"
#include "Engine/World.h"

#include "Defaults/ProjectDefaults.h"
#include "Actors/Fields/FieldTile.h"

AFieldGrid::AFieldGrid()
{
	PrimaryActorTick.bCanEverTick = false;
	TileClass = AFieldTile::StaticClass();
}

void AFieldGrid::BeginPlay()
{
	Super::BeginPlay();
	SpawnFieldTiles();
}

void AFieldGrid::SpawnFieldTiles()
{
	for (int32 i = 0; i < TileAmount.Y; i++)
	{
		for (int32 j = 0; j < TileAmount.X; j++)
		{
			FVector TileLocation = GetTileSpawnLocation(j, i);
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AFieldTile* TileActor = GetWorld()->SpawnActor<AFieldTile>(TileClass, TileLocation, FRotator(0.0f), SpawnInfo);
			TileActors.Add(TileActor);
		}
	}
}

FVector AFieldGrid::GetTileSpawnLocation(int32 Row, int32 Column) const
{
	FVector ActorLocation = GetActorLocation();
	float XOffset = Row * ProjectDefaults::TileSize;
	float YOffset = Column * ProjectDefaults::TileSize;
	FVector TileRelativeLocation = FVector(XOffset, YOffset, 0.0f);
	return ActorLocation + TileRelativeLocation;
}
