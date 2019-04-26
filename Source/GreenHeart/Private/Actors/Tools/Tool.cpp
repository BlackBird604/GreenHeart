// The Green Heart @Politechnika Opolska

#include "Tool.h"
#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"

#include "Defaults/ProjectDefaults.h"
#include "Types/CollisionTypes.h"
#include "Interfaces/ToolAffectable.h"

ATool::ATool()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	ToolMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ToolMesh"));
	ToolMesh->SetupAttachment(SceneRoot);
	ToolMesh->bReceivesDecals = false;

	SetActorHiddenInGame(true);
}

void ATool::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATool::Restore(const FToolInfo& SavedToolInfo)
{
	ToolInfo = SavedToolInfo;
}

bool ATool::Charge()
{
	if (CurrentCharge < ToolInfo.Level && CurrentCharge < ChargeInfo.Num())
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
int32 ATool::Use(const AActor* User)
{
	if (!User || CurrentCharge >= ChargeInfo.Num())
	{
		return 0;
	}

	int32 EnergyDrain = CurrentCharge + 1;
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
				AffectableActor->UseTool(this, CurrentCharge + 1);
			}
		}
	}

	CurrentCharge = 0;
	return EnergyDrain;
}

EToolType ATool::GetType() const
{
	return ToolType;
}

FToolInfo ATool::GetToolInfo()
{
	return ToolInfo;
}

bool ATool::IsSingleUse()
{
	return bIsSingleUse;
}