// The Green Heart @Politechnika Opolska

#include "FeedBox.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Types/CollisionTypes.h"
#include "Actors/Others/Feed.h"


AFeedBox::AFeedBox()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
	CollisionBox->SetCollisionProfileName(CollisionPresets::Interactable);

	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	BoxMesh->SetupAttachment(CollisionBox);

	FeedMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FeedMesh"));
	FeedMesh->SetupAttachment(CollisionBox);
}

void AFeedBox::BeginPlay()
{
	Super::BeginPlay();
	if (!AcceptedFeedClass->IsChildOf(AFeed::StaticClass()))
	{
		AcceptedFeedClass = AFeed::StaticClass();
	}
}

bool AFeedBox::CanInteract(AActor* Item)
{
	if (!Item)
	{
		return false;
	}

	bool bIsFeedAccepted = Item->IsA(AcceptedFeedClass);
	return bIsFeedAccepted && !bHasFeed;
}

void AFeedBox::Interact(AActor* Item)
{

}


