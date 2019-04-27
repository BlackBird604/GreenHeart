// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Structs/ClockInfo.h"
#include "Structs/ToolInfo.h"
#include "Structs/ItemInfo.h"
#include "Structs/BlacksmithInfo.h"
#include "Structs/FarmerState.h"
#include "Enums/StationaryInventoryTypes.h"
#include "Enums/ResourceTypes.h"
#include "FarmingGameMode.generated.h"

class AFarmingGameState;
class UGameHUDWidget;
class UPlayerInventoryWidget;
class UStationaryInventoryWidget;
class APlayerController;
class AFarmer;
class UStationaryToolInventoryWidget;
class UStationaryItemInventoryWidget;
class UBlacksmithWidget;
class USupermarketWidget;

UCLASS()
class GREENHEART_API AFarmingGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	virtual void BeginPlay() override;

	virtual void StartPlay() override;

	void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:
	void OpenPlayerInventory();

	void OpenStationaryInventory(EStationaryInventoryType InventoryType);

	void OpenBlacksmith();

	void OpenSupermarket();

	void RestoreGame();

	void UpdateStationaryInventory(const TArray<FToolInfo>& NewToolInfos);

	void UpdateStationaryInventory(const TArray<FItemInfo>& NewItemInfos);

	bool HasResource(EResourceType ResourceType, int32 Amount);

	void AddResource(EResourceType ResourceType, int32 Amount);

	void RemoveResource(EResourceType ResourceType, int32 Amount);

	void AddNewTool(const FToolInfo& NewToolInfo);

	void UpdateBlacksmithInfo(const FBlacksmithInfo NewInfo);

	void UpgradePlayerTool();

	void UpgradePlayerToolInventory();

	void UpgradePlayerItemInventory();

	FFarmerState GetPlayerState();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup|UMG")
	TSubclassOf<UGameHUDWidget> GameHUDClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup|UMG")
	TSubclassOf<UPlayerInventoryWidget> PlayerInventoryWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup|UMG")
	TSubclassOf<UStationaryToolInventoryWidget> StationaryToolInventoryWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup|UMG")
	TSubclassOf<UStationaryItemInventoryWidget> StationaryItemInventoryWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup|UMG")
	TSubclassOf<UBlacksmithWidget> BlacksmithWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup|UMG")
	TSubclassOf<USupermarketWidget> SupermarketWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ClockMinuteTick = 1.0f;

private:
	void CreateHUD();

	void InitializeManagers();

	void InitializeClockWidget();

	void UpdateClock();

	void OpenStationaryToolInventory();

	void OpenStationaryItemInventory();

	void EnableUIMode();

	void DisableUIMode();

	UFUNCTION()
	void UpdateMoney();

	AFarmingGameState* GameState;

	APlayerController* PlayerController;

	AFarmer* PlayerCharacter;

	UGameHUDWidget* GameHUD;

	FTimerHandle ClockTimer;

	FClockInfo ClockInfo;
};
