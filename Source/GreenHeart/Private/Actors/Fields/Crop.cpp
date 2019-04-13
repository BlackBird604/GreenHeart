// The Green Heart @Politechnika Opolska

#include "Crop.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

ACrop::ACrop()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	RootComponent = CollisionSphere;
	CollisionSphere->SetSphereRadius(20.0f);

	CropMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CropMesh"));
	CropMesh->SetupAttachment(CollisionSphere);
}

void ACrop::BeginPlay()
{
	Super::BeginPlay();
	
}



