// The Green Heart @Politechnika Opolska

#include "Tool.h"
#include "Engine/World.h"

#include "DrawDebugHelpers.h"

ATool::ATool()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ATool::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ATool::Charge()
{
	if (CurrentCharge < MaxCharge || CurrentCharge < AffectedTiles.Num())
	{
		CurrentCharge++;
		return true;
	}

	return false;
}

void ATool::Use(const AActor* User)
{
	if (!User)
	{
		return;
	}

	TArray<FVector2D> TraceOffsets = AffectedTiles[CurrentCharge - 1].TraceOffsets;
	for (FVector2D TraceOffset : TraceOffsets)
	{
		FVector Start = User->GetActorLocation();
		Start += User->GetActorForwardVector() * TraceOffset.X * 100.0f;
		Start += User->GetActorRightVector() * TraceOffset.Y * 100.0f;
		FVector End = Start + FVector(0.0f, 0.0f, -100.f);

		DrawDebugLine(GetWorld(), Start, End, FColor::Green, true, 10);
		TArray<FHitResult> HitResults;
		GetWorld()->LineTraceMultiByChannel(HitResults, Start, End, ECollisionChannel::ECC_Visibility);
	}
	CurrentCharge = 0;
}
