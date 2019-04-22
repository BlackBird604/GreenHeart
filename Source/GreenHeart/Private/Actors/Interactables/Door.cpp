// The Green Heart @Politechnika Opolska

#include "Door.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Defaults/ProjectDefaults.h"
#include "Types/CollisionTypes.h"
#include "Characters/Farmer.h"

ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	float HalfTileSize = ProjectDefaults::TileSize / 2.0f;
	CollisionBox->SetBoxExtent(FVector(HalfTileSize));
	FVector RelativeLocation = FVector(0.0f, 0.0f, CollisionBox->GetScaledBoxExtent().Z);
	CollisionBox->SetRelativeLocation(RelativeLocation);
	CollisionBox->SetCollisionProfileName(CollisionPresets::Interactable);
	CollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Ignore);
	CollisionBox->SetupAttachment(RootComponent);

	PawnBlockingVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnBlockingVolume"));
	float Thickness = 1.0f;
	PawnBlockingVolume->SetBoxExtent(FVector(Thickness, HalfTileSize, HalfTileSize));
	RelativeLocation = FVector(CollisionBox->GetScaledBoxExtent().X, 0.0f, PawnBlockingVolume->GetScaledBoxExtent().Z);
	PawnBlockingVolume->SetRelativeLocation(RelativeLocation);
	PawnBlockingVolume->SetCollisionProfileName(CollisionPresets::Pawn);
	PawnBlockingVolume->SetupAttachment(RootComponent);

	FirstMovementPoint = CreateDefaultSubobject<USceneComponent>(TEXT("FirstMovementPoint"));
	FirstMovementPoint->SetupAttachment(RootComponent);
	FirstMovementPoint->SetRelativeLocation(FVector(200.0f, 0.0f, 0.0f));

	SecondMovementPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SecondMovementPoint"));
	SecondMovementPoint->SetupAttachment(RootComponent);
	SecondMovementPoint->SetRelativeLocation(FVector(-100.0f, 0.0f, 0.0f));

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
		PlayOpenTimeline();
		PawnBlockingVolume->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ADoor::OnClosed()
{
	PawnBlockingVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}