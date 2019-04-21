// The Green Heart @Politechnika Opolska

#include "Crop.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Types/CollisionTypes.h"

ACrop::ACrop()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	RootComponent = CollisionSphere;
	CollisionSphere->SetSphereRadius(20.0f);
	CollisionSphere->SetCollisionProfileName(CollisionPresets::Throwable);
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

bool ACrop::CanBeStored()
{
	return true;
}

FItemInfo ACrop::GetItemInfo()
{
	FItemInfo ItemInfo = FItemInfo();
	ItemInfo.Class = GetClass();
	return ItemInfo;
}

void ACrop::Throw(const FVector& Direction)
{
	CollisionSphere->SetNotifyRigidBodyCollision(true);
	CollisionSphere->OnComponentHit.AddDynamic(this, &ACrop::OnHit);
	ProjectileMovement->Velocity = Direction * HorizontalSpeed;
	ProjectileMovement->Velocity.Z = VerticalSpeed;
	ProjectileMovement->Activate();
}

void ACrop::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();
}


int32 ACrop::GetPrice()
{
	return SellPrice;
}


