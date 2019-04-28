// The Green Heart @Politechnika Opolska

#include "Egg.h"
#include "Components/BoxComponent.h"

#include "Types/CollisionTypes.h"

AEgg::AEgg()
{
	PrimaryActorTick.bCanEverTick = false;
	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetCollisionProfileName(CollisionPresets::Interactable);
	InteractionBox->SetupAttachment(RootComponent);
}

void AEgg::BeginPlay()
{
	Super::BeginPlay();
}

int32 AEgg::GetPrice()
{
	return SellPrice;
}

int32 AEgg::GetEnergyPoints()
{
	return EnergyPoints;
}

bool AEgg::CanBeCollected()
{
	return true;
}

AActor* AEgg::Collect()
{
	OnCollected.Broadcast();
	return this;
}
