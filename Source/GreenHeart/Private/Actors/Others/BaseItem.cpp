// The Green Heart @Politechnika Opolska

#include "BaseItem.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Types/CollisionTypes.h"

ABaseItem::ABaseItem()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	RootComponent = CollisionSphere;
	CollisionSphere->SetSphereRadius(20.0f);
	CollisionSphere->SetCollisionProfileName(CollisionPresets::Throwable);
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ItemMesh->SetupAttachment(CollisionSphere);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->bAutoActivate = false;
	ProjectileMovement->Deactivate();
}

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ABaseItem::CanBeThrown(const FVector& Direction)
{
	return true;
}

bool ABaseItem::CanBeStored()
{
	return true;
}

void ABaseItem::Throw(const FVector& Direction)
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	CollisionSphere->SetNotifyRigidBodyCollision(true);
	CollisionSphere->OnComponentHit.AddDynamic(this, &ABaseItem::OnHit);
	ProjectileMovement->Velocity = Direction * HorizontalSpeed;
	ProjectileMovement->Velocity.Z = VerticalSpeed;
	ProjectileMovement->Activate();
}

FItemInfo ABaseItem::GetItemInfo()
{
	return ItemInfo;
}

void ABaseItem::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();
}
