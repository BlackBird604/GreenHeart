// The Green Heart @Politechnika Opolska

#include "Door.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Types/CollisionTypes.h"
#include "Characters/Farmer.h"

ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
	CollisionBox->SetCollisionProfileName(CollisionPresets::Interactable);


	FirstMovementPoint = CreateDefaultSubobject<USceneComponent>(TEXT("FirstMovementPoint"));
	FirstMovementPoint->SetupAttachment(CollisionBox);

	SecondMovementPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SecondMovementPoint"));
	SecondMovementPoint->SetupAttachment(CollisionBox);
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADoor::Interact()
{
	if (AFarmer* Farmer = Cast<AFarmer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		TArray<FVector> MovementPoints;
		MovementPoints.Add(FirstMovementPoint->GetComponentLocation());
		MovementPoints.Add(SecondMovementPoint->GetComponentLocation());
		Farmer->AutomaticMoveTo(MovementPoints);
	}
}