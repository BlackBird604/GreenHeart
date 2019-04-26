// The Green Heart @Politechnika Opolska

#include "FarmingGameMode.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "GameFramework/PlayerController.h"

#include "Fundamentals/FarmingGameInstance.h"
#include "Fundamentals/FarmingGameState.h"
#include "Actors/Managers/ManagerBase.h"
#include "Actors/Others/FarmerSpawnPoint.h"
#include "Widgets/GameHUDWidget.h"
#include "Widgets/PlayerInventoryWidget.h"
#include "Characters/Farmer.h"
#include "Widgets/StationaryToolInventoryWidget.h"
#include "Widgets/StationaryItemInventoryWidget.h"
#include "Widgets/BlacksmithWidget.h"

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
	PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerCharacter = Cast<AFarmer>(UGameplayStatics::GetPlayerCharacter(this, 0));
	GameState = GetWorld()->GetGameState<AFarmingGameState>();
	if (GameState)
	{
		GameState->OnMoneyChanged.AddDynamic(this, &AFarmingGameMode::UpdateMoney);
	}

	InitializeManagers();
	InitializeClockWidget();
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

void AFarmingGameMode::InitializeClockWidget()
{
	if (GameState && GameHUD)
	{
		ClockInfo = GameState->GetClockInfo();
		GetWorldTimerManager().SetTimer(ClockTimer, this, &AFarmingGameMode::UpdateClock, ClockMinuteTick, true, ClockMinuteTick);
		GameHUD->UpdateClock(ClockInfo);

		UpdateMoney();
	}
}

void AFarmingGameMode::UpdateClock()
{
	ClockInfo.AddMinutes(1);
	GameHUD->UpdateClock(ClockInfo);
}

void AFarmingGameMode::UpdateMoney()
{
	if (GameState && GameHUD)
	{
		int32 CurrentMoneyAmount = GameState->GetResourceAmount(EResourceType::Money);
		GameHUD->UpdateMoney(CurrentMoneyAmount);
	}
}

void AFarmingGameMode::OpenPlayerInventory()
{
	if (!PlayerController || !PlayerCharacter)
	{
		return;
	}


	UPlayerInventoryWidget* PlayerInventoryWidget = CreateWidget<UPlayerInventoryWidget>(GetWorld(), PlayerInventoryWidgetClass);
	if (PlayerInventoryWidget)
	{
		PlayerInventoryWidget->AddToViewport(2);
		EnableUIMode();
		PlayerInventoryWidget->PopulateSlots(PlayerCharacter);
	}
}

void AFarmingGameMode::OpenStationaryInventory(EStationaryInventoryType InventoryType)
{
	if (GameState)
	{
		switch (InventoryType)
		{
		case EStationaryInventoryType::Tool:
			OpenStationaryToolInventory();
			break;
		case EStationaryInventoryType::Item:
			OpenStationaryItemInventory();
			break;
		}
	}
}

void AFarmingGameMode::OpenStationaryToolInventory()
{
	UStationaryToolInventoryWidget* StationaryInventoryWidget = CreateWidget<UStationaryToolInventoryWidget>(GetWorld(), StationaryToolInventoryWidgetClass);
	if (StationaryInventoryWidget)
	{
		StationaryInventoryWidget->AddToViewport(2);
		EnableUIMode();
		StationaryInventoryWidget->PopulateSlots(PlayerCharacter, GameState->GetStationaryToolInventoryInfo());
	}
}

void AFarmingGameMode::OpenStationaryItemInventory()
{
	UStationaryItemInventoryWidget* StationaryInventoryWidget = CreateWidget<UStationaryItemInventoryWidget>(GetWorld(), StationaryItemInventoryWidgetClass);
	if (StationaryInventoryWidget)
	{
		StationaryInventoryWidget->AddToViewport(2);
		EnableUIMode();
		StationaryInventoryWidget->PopulateSlots(PlayerCharacter, GameState->GetStationaryItemInventoryInfo());
	}
}

void AFarmingGameMode::OpenBlacksmith()
{
	if (!GameState)
	{
		return;
	}
	UBlacksmithWidget* BlacksmithWidget = CreateWidget<UBlacksmithWidget>(GetWorld(), BlacksmithWidgetClass);
	if (BlacksmithWidget)
	{
		BlacksmithWidget->AddToViewport(2);
		EnableUIMode();
		BlacksmithWidget->SetupWidget(GameState->GetBlacksmithInfo());
	}
}

void AFarmingGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GameState->SetClockInfo(ClockInfo);
}

void AFarmingGameMode::RestoreGame()
{
	DisableUIMode();
}

void AFarmingGameMode::EnableUIMode()
{
	if (PlayerController)
	{
		PlayerController->SetInputMode(FInputModeGameAndUI());
		PlayerController->bShowMouseCursor = true;
	}
	if (PlayerCharacter)
	{
		PlayerCharacter->ClearMovementInput();
	}
}

void AFarmingGameMode::DisableUIMode()
{
	if (PlayerController)
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->bShowMouseCursor = false;
	}
}

void AFarmingGameMode::UpdateStationaryInventory(const TArray<FToolInfo>& NewToolInfos)
{
	if (GameState)
	{
		GameState->SetStationaryInventoryInfo(NewToolInfos);
	}
}

void AFarmingGameMode::UpdateStationaryInventory(const TArray<FItemInfo>& NewItemInfos)
{
	if (GameState)
	{
		GameState->SetStationaryInventoryInfo(NewItemInfos);
	}
}