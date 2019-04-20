// The Green Heart @Politechnika Opolska

#include "Teleporter.h"
#include "Components/BoxComponent.h"

#include "Characters/Farmer.h"
#include "Fundamentals/FarmingGameInstance.h"

ATeleporter::ATeleporter()
{
	PrimaryActorTick.bCanEverTick = false;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
	CollisionBox->SetGenerateOverlapEvents(true);
}

void ATeleporter::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ATeleporter::OnBoxBeginOverlap);
}

void ATeleporter::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AFarmer* Farmer = Cast<AFarmer>(OtherActor))
	{
		if (UFarmingGameInstance* GameInstance = Cast<UFarmingGameInstance>(GetGameInstance()))
		{
			GameInstance->OpenLevel(NewLevelName, NewSpawnPoint);
		}
	}
}



