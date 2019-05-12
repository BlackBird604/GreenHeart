// The Green Heart @Politechnika Opolska

#include "Bed.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ArrowComponent.h"

#include "Types/CollisionTypes.h"
#include "Characters/Farmer.h"

ABed::ABed()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
	CollisionBox->SetCollisionProfileName(CollisionPresets::Interactable);

	BedMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BedMesh"));
	BedMesh->SetupAttachment(CollisionBox);

	BedJumpTarget = CreateDefaultSubobject<UArrowComponent>(TEXT("BedJumpTarget"));
	BedJumpTarget->SetupAttachment(CollisionBox);
}

void ABed::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABed::Interact()
{
	AFarmer* PlayerCharacter = Cast<AFarmer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter)
	{
		FVector TargetLocation = BedJumpTarget->GetComponentToWorld().GetLocation();
		FRotator TargetRotation = BedJumpTarget->GetComponentToWorld().GetRotation().Rotator();
		PlayerCharacter->GoToBed(TargetLocation, TargetRotation);
	}
}


