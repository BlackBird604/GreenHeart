// The Green Heart @Politechnika Opolska

#include "Animal.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

#include "Types/CollisionTypes.h"
#include "Actors/Tools/Tool.h"

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

void AAnimal::RestoreState(const FAnimalState& AnimalState)
{
	CurrentState = AnimalState;
}

FAnimalState AAnimal::GetCurrentState()
{
	return CurrentState;
}

void AAnimal::UseTool(const ATool* Instigator, int32 Strength)
{
	if (!Instigator)
	{
		return;
	}

	switch (Instigator->GetType())
	{
		case EToolType::Hoe:
		case EToolType::Hammer:
		case EToolType::Scythe:
			ApplyDamage();
			break;
	}
}

void AAnimal::ApplyDamage()
{
	UE_LOG(LogTemp, Warning, TEXT("ToolHIT!"));
}

