// The Green Heart @Politechnika Opolska

#include "FarmingGameMode.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "GameFramework/PlayerController.h"

#include "Fundamentals/FarmingGameInstance.h"
#include "Fundamentals/FarmingGameState.h"
#include "Actors/Others/DeferrableActor.h"
#include "Actors/Others/FarmerSpawnPoint.h"
#include "Widgets/GameHUDWidget.h"
#include "Widgets/PlayerInventoryWidget.h"
#include "Characters/Farmer.h"
#include "Widgets/StationaryToolInventoryWidget.h"
#include "Widgets/StationaryItemInventoryWidget.h"
#include "Widgets/BlacksmithWidget.h"
#include "Widgets/SupermarketWidget.h"
#include "Widgets/HouseBuilderWidget.h"
#include "Widgets/MessageboxWidget.h"

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
	DisableUIMode();
}

void AFarmingGameMode::InitializeManagers()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(this, ADeferrableActor::StaticClass(), FoundActors);
	for (AActor* FoundActor : FoundActors)
	{
		ADeferrableActor* Defferable = Cast<ADeferrableActor>(FoundActor);
		Defferable->StartPlay();
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
	if (ClockInfo.Hour == EndDayHour)
	{
		GetWorldTimerManager().ClearTimer(ClockTimer);
		UMessageboxWidget* MessageboxWidget = OpenMessagebox(FText::FromString("It's getting late. I should go to bed now."));
		if (MessageboxWidget)
		{
			MessageboxWidget->OnClosed.AddDynamic(this, &AFarmingGameMode::EndDay);
		}
	}
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

void AFarmingGameMode::OpenStationaryInventory(EStationaryInventoryType InventoryType, AActor* InventoryActor)
{
	if (GameState)
	{
		switch (InventoryType)
		{
		case EStationaryInventoryType::Tool:
			OpenStationaryToolInventory(InventoryActor);
			break;
		case EStationaryInventoryType::Item:
			OpenStationaryItemInventory(InventoryActor);
			break;
		}
	}
}

void AFarmingGameMode::OpenStationaryToolInventory(AActor* InventoryActor)
{
	UStationaryToolInventoryWidget* StationaryInventoryWidget = CreateWidget<UStationaryToolInventoryWidget>(GetWorld(), StationaryToolInventoryWidgetClass);
	if (StationaryInventoryWidget)
	{
		StationaryInventoryWidget->AddToViewport(2);
		EnableUIMode();
		StationaryInventoryWidget->SetInventoryActor(InventoryActor);
		StationaryInventoryWidget->PopulateSlots(PlayerCharacter, GameState->GetStationaryToolInventoryInfo());
	}
}

void AFarmingGameMode::OpenStationaryItemInventory(AActor* InventoryActor)
{
	UStationaryItemInventoryWidget* StationaryInventoryWidget = CreateWidget<UStationaryItemInventoryWidget>(GetWorld(), StationaryItemInventoryWidgetClass);
	if (StationaryInventoryWidget)
	{
		StationaryInventoryWidget->AddToViewport(2);
		EnableUIMode();
		StationaryInventoryWidget->SetInventoryActor(InventoryActor);
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
		BlacksmithWidget->SetupWidget(PlayerCharacter->GetCurrentState(), GameState->GetBlacksmithInfo());
	}
}

void AFarmingGameMode::OpenSupermarket()
{
	if (!GameState)
	{
		return;
	}
	USupermarketWidget* SupermarketWidget = CreateWidget<USupermarketWidget>(GetWorld(), SupermarketWidgetClass);
	if (SupermarketWidget)
	{
		SupermarketWidget->AddToViewport(2);
		EnableUIMode();
		SupermarketWidget->SetupWidget(GameState->GetSupermarketInfo());
	}
}

void AFarmingGameMode::OpenHouseBuilder()
{
	if (!GameState)
	{
		return;
	}
	UHouseBuilderWidget* HouseBuilderWidget = CreateWidget<UHouseBuilderWidget>(GetWorld(), HouseBuilderWidgetClass);
	if (HouseBuilderWidget)
	{
		HouseBuilderWidget->AddToViewport(2);
		EnableUIMode();
		HouseBuilderWidget->SetupWidget(GameState->GetConstructionStates());
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
		PlayerController->bShowMouseCursor = true;
		FInputModeGameAndUI InputMode;
		InputMode.SetHideCursorDuringCapture(false);
		PlayerController->SetInputMode(InputMode);
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

bool AFarmingGameMode::HasResource(EResourceType ResourceType, int32 Amount)
{
	if (GameState)
	{
		int32 OwnedAmount = GameState->GetResourceAmount(ResourceType);
		return OwnedAmount >= Amount;
	}
	return false;
}

void AFarmingGameMode::AddResource(EResourceType ResourceType, int32 Amount)
{
	if (GameState)
	{
		GameState->AddResource(ResourceType, Amount);
	}
}

void AFarmingGameMode::RemoveResource(EResourceType ResourceType, int32 Amount)
{
	if (GameState)
	{
		GameState->RemoveResource(ResourceType, Amount);
	}
}

void AFarmingGameMode::AddNewTool(const FToolInfo& NewToolInfo)
{
	if (GameState && PlayerCharacter)
	{
		if (PlayerCharacter->IsToolInventoryFull())
		{
			GameState->AddToolToStationaryInventory(NewToolInfo);
		}
		else
		{
			PlayerCharacter->AddTool(NewToolInfo);
		}
	}
}

void AFarmingGameMode::UpdateBlacksmithInfo(const FBlacksmithInfo NewInfo)
{
	if (GameState)
	{
		GameState->SetBlacksmithInfo(NewInfo);
	}
}

void AFarmingGameMode::UpgradePlayerTool()
{
	if (PlayerCharacter)
	{
		FFarmerState FarmerState = PlayerCharacter->GetCurrentState();
		FToolInventoryState ToolInventory = FarmerState.ToolInventoryState;
		ToolInventory.UpdateCurrentTool();
		PlayerCharacter->UpdateToolInventory(ToolInventory.ToolInfos);
	}
}

void AFarmingGameMode::UpgradePlayerToolInventory()
{
	if (PlayerCharacter)
	{
		PlayerCharacter->UpgradeToolInventory();
	}
}

void AFarmingGameMode::UpgradePlayerItemInventory()
{
	if (PlayerCharacter)
	{
		PlayerCharacter->UpgradeItemInventory();
	}
}

FFarmerState AFarmingGameMode::GetPlayerState()
{
	if (PlayerCharacter)
	{
		return PlayerCharacter->GetCurrentState();
	}
	return FFarmerState();
}

void AFarmingGameMode::AddAnimal(EAnimalType AnimalType)
{
	if (GameState)
	{
		switch (AnimalType)
		{
		case EAnimalType::Cow:
			GameState->AddCow();
			break;
		case EAnimalType::Chicken:
			GameState->AddChcicken();
			break;
		}
	}
}

void AFarmingGameMode::StartConstructionUpgrade(EConstructionType ConstructionType)
{
	if (GameState)
	{
		GameState->StartConstructionUpgrade(ConstructionType);
	}
}

bool AFarmingGameMode::CanBuyAnimal(EAnimalType AnimalType)
{
	int32 BuildingLevel = 0;
	int32 MaxAnimalAmount = 0;
	int32 CurrentAnimalAmount = 0;

	switch (AnimalType)
	{
	case EAnimalType::Cow:
		BuildingLevel = GameState->GetConstructionState(EConstructionType::Barn).CurrentLevel;
		MaxAnimalAmount = BuildingLevel * CowsPerBuildingLevel;
		CurrentAnimalAmount = GameState->GetCowAmount();
		return CurrentAnimalAmount < MaxAnimalAmount;

	case EAnimalType::Chicken:
		BuildingLevel = GameState->GetConstructionState(EConstructionType::ChickenCoop).CurrentLevel;
		MaxAnimalAmount = BuildingLevel * ChickensPerBuildingLevel;
		CurrentAnimalAmount = GameState->GetChickenAmount();
		return CurrentAnimalAmount < MaxAnimalAmount;
	}
	return false;
}

bool AFarmingGameMode::IsConstructionInProgress()
{
	if (GameState)
	{
		TArray<FConstructionState> ConstructionStates = GameState->GetConstructionStates();
		for (int32 i = 0; i < ConstructionStates.Num(); i++)
		{
			if (ConstructionStates[i].bIsUnderConstruction)
			{
				return true;
			}
		}
	}
	return false;
}

void AFarmingGameMode::OnPlayerOutOfEnergy()
{
	GetWorldTimerManager().ClearTimer(ClockTimer);
	UMessageboxWidget* MessageboxWidget = OpenMessagebox(FText::FromString("I'm exhausted! I need to rest."));
	if (MessageboxWidget)
	{
		MessageboxWidget->OnClosed.AddDynamic(this, &AFarmingGameMode::EndDay);
	}
}

UMessageboxWidget* AFarmingGameMode::OpenMessagebox(FText NewMessage)
{
	UMessageboxWidget* MessageboxWidget = CreateWidget<UMessageboxWidget>(GetWorld(), MessageboxWidgetClass);
	if (MessageboxWidget)
	{
		MessageboxWidget->AddToViewport(3);
		EnableUIMode();
		if (PlayerController)
		{
			PlayerController->bShowMouseCursor = false;
		}
		MessageboxWidget->SetMessage(NewMessage);
	}
	return MessageboxWidget;
}

void AFarmingGameMode::EndDay()
{
	if (UFarmingGameInstance* GameInstance = GetGameInstance<UFarmingGameInstance>())
	{
		GameInstance->StartNextDay();
	}
}