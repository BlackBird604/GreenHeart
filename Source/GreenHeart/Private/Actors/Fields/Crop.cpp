// The Green Heart @Politechnika Opolska

#include "Crop.h"


ACrop::ACrop()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ACrop::BeginPlay()
{
	Super::BeginPlay();
}

int32 ACrop::GetPrice()
{
	return SellPrice;
}

int32 ACrop::GetEnergyPoints()
{
	return EnergyPoints;
}

UAnimMontage* ACrop::GetConsumeMontage()
{
	return ConsumeMontage;
}