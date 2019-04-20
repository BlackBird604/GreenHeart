// The Green Heart @Politechnika Opolska

#include "SalesContainer.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "Interfaces/Sellable.h"

ASalesContainer::ASalesContainer()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
	CollisionBox->SetGenerateOverlapEvents(true);
	
	ContainerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ContainerMesh"));
	ContainerMesh->SetupAttachment(CollisionBox);
	ContainerMesh->bReceivesDecals = false;
}

void ASalesContainer::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ASalesContainer::OnBoxBeginOverlap);
	
}

void ASalesContainer::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ISellable* Sellable = Cast<ISellable>(OtherActor))
	{
		OtherActor->Destroy();
	}
}