// The Green Heart @Politechnika Opolska

#include "Bed.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Fundamentals/FarmingGameInstance.h"

ABed::ABed()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
	CollisionBox->SetGenerateOverlapEvents(true);

	BedMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BedMesh"));
	BedMesh->SetupAttachment(CollisionBox);
}

void ABed::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABed::Interact()
{
	if (UFarmingGameInstance* GameInstance = Cast<UFarmingGameInstance>(GetGameInstance()))
	{
		GameInstance->StartNextDay();
	}
}


