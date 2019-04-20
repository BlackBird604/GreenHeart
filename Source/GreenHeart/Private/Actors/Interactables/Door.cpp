// The Green Heart @Politechnika Opolska

#include "Door.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"

ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
	CollisionBox->SetGenerateOverlapEvents(true);

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

}