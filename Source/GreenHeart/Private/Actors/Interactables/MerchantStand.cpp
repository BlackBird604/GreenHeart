// The Green Heart @Politechnika Opolska

#include "MerchantStand.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"

#include "Types/CollisionTypes.h"
#include "Fundamentals/FarmingGameMode.h"

AMerchantStand::AMerchantStand()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
	CollisionBox->SetCollisionProfileName(CollisionPresets::Interactable);

	StandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StandMesh"));
	StandMesh->SetupAttachment(CollisionBox);
}

void AMerchantStand::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMerchantStand::Interact()
{
	if (AFarmingGameMode* GameMode = GetWorld()->GetAuthGameMode<AFarmingGameMode>())
	{
		GameMode->OpenBlacksmith();
	}
}
