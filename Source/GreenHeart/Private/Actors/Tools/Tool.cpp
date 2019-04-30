// The Green Heart @Politechnika Opolska

#include "Tool.h"
#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

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
	SetupMaterial(ToolInfo.CurrentLevel);
}

bool ATool::Charge()
{
	if (CurrentCharge < ToolInfo.CurrentLevel && CurrentCharge < ChargeInfo.Num())
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

int32 ATool::Use(const AActor* User)
{
	if (!User || CurrentCharge >= ChargeInfo.Num())
	{
		return 0;
	}

	AffectedActors.Empty();
	int32 EnergyDrain = CurrentCharge + 1;
	TArray<FVector2D> TraceOffsets = ChargeInfo[CurrentCharge].TraceOffsets;
	for (FVector2D TraceOffset : TraceOffsets)
	{
		float TileSize = ProjectDefaults::TileSize;
		FVector TraceStart = User->GetActorLocation();
		TraceStart += User->GetActorForwardVector() * TraceOffset.X * TileSize;
		TraceStart += User->GetActorRightVector() * TraceOffset.Y * TileSize;
		UseLocations.Add(TraceStart);
	}

	if (SequenceUseDelay <= 0)
	{
		PerformInstantUse();
	}
	else
	{
		GetWorldTimerManager().SetTimer(SequenceUseTimer, this, &ATool::PerformSequenceUse, SequenceUseDelay, true, 0.0f);
	}
	return EnergyDrain;
}

void ATool::PerformInstantUse()
{
	for (const FVector& Location : UseLocations)
	{
		UseAtLocation(Location);
	}
	UseLocations.Empty();
	CurrentCharge = 0;
}

void ATool::PerformSequenceUse()
{
	if (UseLocations.Num() > 0)
	{
		FVector Location = UseLocations[0];
		UseLocations.RemoveAt(0);
		UseAtLocation(Location);
	}

	if (UseLocations.Num() == 0)
	{
		GetWorldTimerManager().ClearTimer(SequenceUseTimer);
		CurrentCharge = 0;
	}
}

void ATool::UseAtLocation(const FVector& Location)
{
	OnUse(Location.GridSnap(ProjectDefaults::TileSize));
	FVector GridLocation = Location.GridSnap(100.0f);
	float TraceLength = 100.0f;
	FVector TraceEnd = Location + FVector(0.0f, 0.0f, -TraceLength);
	TArray<FHitResult> HitResults;
	GetWorld()->LineTraceMultiByChannel(HitResults, Location, TraceEnd, ECC_ToolTrace);
	for (FHitResult HitResult : HitResults)
	{
		IToolAffectable* AffectableActor = Cast<IToolAffectable>(HitResult.Actor);
		if (AffectableActor)
		{
			OnAffectedUse(Location.GridSnap(ProjectDefaults::TileSize));
			AffectedActors.Add(HitResult.GetActor());
			AffectableActor->UseTool(this, CurrentCharge + 1);
		}
	}
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

TArray<AActor*> ATool::GetAffectedActors()
{
	return AffectedActors;
}