// The Green Heart @Politechnika Opolska

#include "Tool.h"
#include "Engine/World.h"
#include "Interfaces/ToolAffectable.h"
#include "Defaults/ProjectDefaults.h"

#include "Types/CollisionTypes.h"
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
	if (CurrentCharge < MaxCharge && CurrentCharge < ChargeInfo.Num())
	{
		CurrentCharge++;
		return true;
	}
	return false;
}

UAnimMontage* ATool::GetChargeMontage()
{
	if (CurrentCharge < ChargeInfo.Num())
	{
		return ChargeInfo[CurrentCharge].Montage;
	}
	return nullptr;
}

UAnimMontage* ATool::GetUseMontage()
{
	return UseMontage;
}

//REFACTORING
void ATool::Use(const AActor* User)
{
	if (!User || CurrentCharge >= ChargeInfo.Num())
	{
		return;
	}

	TArray<FVector2D> TraceOffsets = ChargeInfo[CurrentCharge].TraceOffsets;
	for (FVector2D TraceOffset : TraceOffsets)
	{
		float TileSize = ProjectDefaults::TileSize;
		float TraceLength = 100.0f;
		FVector TraceStart = User->GetActorLocation();
		TraceStart += User->GetActorForwardVector() * TraceOffset.X * TileSize;
		TraceStart += User->GetActorRightVector() * TraceOffset.Y * TileSize;
		FVector TraceEnd = TraceStart + FVector(0.0f, 0.0f, -TraceLength);

		TArray<FHitResult> HitResults;
		GetWorld()->LineTraceMultiByChannel(HitResults, TraceStart, TraceEnd, ECC_ToolTrace);
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
