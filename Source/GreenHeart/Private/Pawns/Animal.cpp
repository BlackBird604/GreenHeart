// The Green Heart @Politechnika Opolska

#include "Animal.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

#include "Types/CollisionTypes.h"

AAnimal::AAnimal()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetCollisionProfileName(CollisionPresets::Pawn);
	RootComponent = CollisionBox;

	AnimalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("AnimalMesh"));
	AnimalMesh->SetupAttachment(CollisionBox);

	MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = CollisionBox;
}

void AAnimal::BeginPlay()
{
	Super::BeginPlay();
	
}

