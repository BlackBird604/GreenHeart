// The Green Heart @Politechnika Opolska

#include "FieldGrid.h"
#include "Engine/World.h"

#include "Defaults/ProjectDefaults.h"
#include "Fundamentals/FarmingGameInstance.h"
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
	RestoreState();
}

void AFieldGrid::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	SaveState();
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

void AFieldGrid::SaveState()
{
	FFieldGridState State;
	for (AFieldTile* TileActor : TileActors)
	{
		if (TileActor)
		{
			State.TileStates.Add(TileActor->GetState());
		}
		else
		{
			State.TileStates.Add(FFieldTileState());
		}
	}

	UFarmingGameInstance* GameInstance = Cast<UFarmingGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->SetGridState(State);
	}
}

void AFieldGrid::RestoreState()
{
	UFarmingGameInstance* GameInstance = Cast<UFarmingGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		FFieldGridState State = GameInstance->GetGridState();
		for (int32 i = 0; i < State.TileStates.Num(); i++)
		{
			if (TileActors[i])
			{
				TileActors[i]->RestoreState(State.TileStates[i]);
			}
		}
	}
}