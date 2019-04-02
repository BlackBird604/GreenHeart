// The Green Heart @Politechnika Opolska

#include "Tool.h"
#include "Engine/World.h"
#include "Interfaces/ToolAffectable.h"
#include "Defaults/ProjectDefaults.h"

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
		float TileSize = ProjectDefaults::TileSize;
		float TraceLength = 100;
		FVector TraceStart = User->GetActorLocation();
		TraceStart += User->GetActorForwardVector() * TraceOffset.X * TileSize;
		TraceStart += User->GetActorRightVector() * TraceOffset.Y * TileSize;
		FVector TraceEnd = TraceStart + FVector(0.0f, 0.0f, -TraceLength);

		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, true, 10); // TEMPORARY

		TArray<FHitResult> HitResults;
		GetWorld()->LineTraceMultiByChannel(HitResults, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);
		for (FHitResult HitResult : HitResults)
		{
			IToolAffectable* AffectableActor = Cast<IToolAffectable>(HitResult.Actor);
			if (AffectableActor)
			{
				AffectableActor->UseTool(this);
			}
		}

	}
	CurrentCharge = 0;
}

EToolType ATool::GetType() const
{
	return ToolType;
}
