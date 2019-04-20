// The Green Heart @Politechnika Opolska

#include "Crop.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ACrop::ACrop()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	RootComponent = CollisionSphere;
	CollisionSphere->SetSphereRadius(20.0f);

	CropMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CropMesh"));
	CropMesh->SetupAttachment(CollisionSphere);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->bAutoActivate = false;
	ProjectileMovement->Deactivate();
}

void ACrop::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ACrop::CanBeThrown(const FVector& Direction)
{
	return true;
}

void ACrop::Throw(const FVector& Direction)
{
	ProjectileMovement->Velocity = Direction * HorizontalSpeed;
	ProjectileMovement->Velocity.Z = VerticalSpeed;
	ProjectileMovement->Activate();
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

int32 ACrop::GetPrice()
{
	return SellPrice;
}


