// The Green Heart @Politechnika Opolska

#include "Crop.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Types/CollisionTypes.h"

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


