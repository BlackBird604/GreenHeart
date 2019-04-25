// The Green Heart @Politechnika Opolska

#include "FarmingGameMode.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

#include "Fundamentals/FarmingGameInstance.h"
#include "Fundamentals/FarmingGameState.h"
#include "Actors/Managers/ManagerBase.h"
#include "Actors/Others/FarmerSpawnPoint.h"
#include "Widgets/GameHUDWidget.h"

AActor* AFarmingGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	Super::ChoosePlayerStart_Implementation(Player);
	if (UFarmingGameInstance* GameInstance = Cast<UFarmingGameInstance>(GetGameInstance()))
	{
		int32 SpawnPointIndex = GameInstance->GetSpawnPointIndex();
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(this, AFarmerSpawnPoint::StaticClass(), FoundActors);
		for (AActor* FoundActor : FoundActors)
		{
			AFarmerSpawnPoint* SpawnPoint = Cast<AFarmerSpawnPoint>(FoundActor);
			int32 FoundID = SpawnPoint->GetID();
			if (SpawnPointIndex == FoundID)
			{
				return SpawnPoint;
			}
		}
	}
	return nullptr;
}

void AFarmingGameMode::BeginPlay()
{
	Super::BeginPlay();
	AFarmingGameMode::CreateHUD();
}

void AFarmingGameMode::CreateHUD()
{
	GameHUD = CreateWidget<UGameHUDWidget>(GetWorld(), GameHUDClass);
	if (GameHUD)
	{
		GameHUD->AddToViewport(1);
	}
}

void AFarmingGameMode::StartPlay()
{
	Super::StartPlay();
	GameState = GetWorld()->GetGameState<AFarmingGameState>();

	InitializeManagers();
	InitializeClock();
}

void AFarmingGameMode::InitializeManagers()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(this, AManagerBase::StaticClass(), FoundActors);
	for (AActor* FoundActor : FoundActors)
	{
		AManagerBase* Manager = Cast<AManagerBase>(FoundActor);
		Manager->StartPlay();
	}
}

void AFarmingGameMode::InitializeClock()
{
	if (GameState && GameHUD)
	{
		ClockInfo = GameState->GetClockInfo();
		GetWorldTimerManager().SetTimer(ClockTimer, this, &AFarmingGameMode::UpdateClock, ClockMinuteTick, true, ClockMinuteTick);
		GameHUD->UpdateClock(ClockInfo);
	}
}

void AFarmingGameMode::UpdateClock()
{
	ClockInfo.AddMinutes(1);
	GameHUD->UpdateClock(ClockInfo);
}

void AFarmingGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GameState->SetClockInfo(ClockInfo);
}
