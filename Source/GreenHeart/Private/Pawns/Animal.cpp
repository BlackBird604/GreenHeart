// The Green Heart @Politechnika Opolska

#include "Animal.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Engine/World.h"
#include "TimerManager.h"

#include "Types/CollisionTypes.h"
#include "Actors/Tools/Tool.h"

AAnimal::AAnimal()
{
	PrimaryActorTick.bCanEverTick = true;

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
	SetActionTimer(1.0f, 2.0f);
}

void AAnimal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bShouldMove && !IsMovementBlocked())
	{
		AddMovementInput(GetActorForwardVector());
	}

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

void AAnimal::PerformNextAction()
{
	UE_LOG(LogTemp, Warning, TEXT("ToolHIT!"));
	if (IsMovementBlocked())
	{
		Turn();
		bShouldMove = false;
		SetActionTimer(0.5f, 2.0f);
		return;
	}

	if (FMath::RandBool())
	{
		bShouldMove = true;
		SetActionTimer(2.0f, 4.0f);
		return;
	}

	if (bShouldMove)
	{
		bShouldMove = false;
		SetActionTimer(1.0f, 2.0f);
		return;
	}

	if (FMath::RandBool())
	{
		Turn();
		bShouldMove = false;
		SetActionTimer(1.0f, 2.0f);
		return;
	}

	SetActionTimer(1.0f, 2.0f);
}

void AAnimal::SetActionTimer(float MinDelay, float MaxDelay)
{
	GetWorldTimerManager().SetTimer(ActionTimer, this, &AAnimal::PerformNextAction, FMath::RandRange(MinDelay, MaxDelay), false);
}

bool AAnimal::IsMovementBlocked()
{
	FHitResult HitResult;
	float CollisionBoxLengthExtent = CollisionBox->GetScaledBoxExtent().X;
	float CollisionBoxWidthExtent = CollisionBox->GetScaledBoxExtent().Y;
	FVector ActorFrontLocation = GetActorLocation() + GetActorForwardVector() * CollisionBoxLengthExtent;
	float DetectionOffset = 1.0f;
	ActorFrontLocation += GetActorForwardVector() * DetectionOffset;
	FVector LeftSide = ActorFrontLocation - GetActorRightVector() * CollisionBoxWidthExtent;
	FVector RightSide = ActorFrontLocation + GetActorRightVector() * CollisionBoxWidthExtent;
	GetWorld()->LineTraceSingleByChannel(HitResult, LeftSide, RightSide, ECollisionChannel::ECC_Pawn);
	return HitResult.bBlockingHit;
}

void AAnimal::Turn()
{
	float YawRotationToAdd = 90.0f;
	if (FMath::RandBool())
	{
		YawRotationToAdd = -YawRotationToAdd;
	}
	FRotator ActorRotation = GetActorRotation();
	ActorRotation.Yaw = FMath::RoundToFloat(ActorRotation.Yaw + YawRotationToAdd);
	SetActorRotation(ActorRotation);
}
