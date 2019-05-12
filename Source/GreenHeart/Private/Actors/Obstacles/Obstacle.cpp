// The Green Heart @Politechnika Opolska

#include "Obstacle.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Defaults/ProjectDefaults.h"
#include "Types/CollisionTypes.h"
#include "Actors/Tools/Tool.h"
#include "Actors/Others/DestroyActor.h"

AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = false;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	float TileSize = ProjectDefaults::TileSize;
	FVector BoxExtent = FVector(TileSize / 2.0f);
	CollisionBox->SetBoxExtent(BoxExtent);
	RootComponent = CollisionBox;
	CollisionBox->SetCollisionProfileName(CollisionPresets::Obstacle);
	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObstacleMesh"));
	ObstacleMesh->SetupAttachment(CollisionBox);
	ObstacleMesh->bReceivesDecals = false;

}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

void AObstacle::UseTool(const ATool* Instigator, int32 Strength)
{
	if (Instigator->GetType() == AffectedByTool)
	{
		ApplyDamage(Strength);
		
		if (HealthPoints <= 0)
		{
			OnObstacleDestroyed.Broadcast(this);
			SpawnDestroyActor();
			Destroy();
		}
	}
}

void AObstacle::ApplyDamage(int32 Strength)
{
	int32 Power = Strength - RequiredStrength;
	int32 Damage = FMath::Pow(2, Power);
	HealthPoints -= Damage;
}

void AObstacle::SpawnDestroyActor()
{
	FActorSpawnParameters SpawnInfo;
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<ADestroyActor>(DestroyActorClass, SpawnLocation, SpawnRotation, SpawnInfo);
}