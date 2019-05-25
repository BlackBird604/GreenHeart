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
#include "Enums/AnimalTypes.h"
#include "Enums/ConstructionTypes.h"
#include "FarmingGameMode.generated.h"

class UAudioComponent;
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
class UHouseBuilderWidget;
class UMessageboxWidget;
class USoundWave;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTimeUpdatedSigneture, int32, NewHour, int32, NewMinute);

UCLASS()
class GREENHEART_API AFarmingGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFarmingGameMode();

protected:
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	virtual void BeginPlay() override;

	virtual void StartPlay() override;

	void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:
	void OpenPlayerInventory();

	void OpenStationaryInventory(EStationaryInventoryType InventoryType, AActor* InventoryActor);

	void OpenBlacksmith();

	void OpenSupermarket();

	void OpenHouseBuilder();

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

	void AddAnimal(EAnimalType AnimalType);

	void StartConstructionUpgrade(EConstructionType ConstructionType);

	bool CanBuyAnimal(EAnimalType AnimalType);

	bool IsConstructionInProgress();

	void OnPlayerOutOfEnergy();

	UPROPERTY(BlueprintAssignable)
	FOnTimeUpdatedSigneture OnTimeUpdated;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UAudioComponent* AudioComponent;

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

	UPROPERTY(EditDefaultsOnly, Category = "Setup|UMG")
	TSubclassOf<UHouseBuilderWidget> HouseBuilderWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup|UMG")
	TSubclassOf<UMessageboxWidget> MessageboxWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ClockMinuteTick = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 CowsPerBuildingLevel = 10;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 ChickensPerBuildingLevel = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 EndDayHour = 20;

private:
	UFUNCTION()
		void OnAudioPercentUpdated(const USoundWave* PlayingSoundWave, const float PlaybackPercent);

	void CreateHUD();

	void InitializeManagers();

	void InitializeClockWidget();

	void UpdateClock();

	void OpenStationaryToolInventory(AActor* InventoryActor);

	void OpenStationaryItemInventory(AActor* InventoryActor);

	void EnableUIMode();

	void DisableUIMode();

	UMessageboxWidget* OpenMessagebox(FText NewMessage);

	UFUNCTION()
	void EndDay();

	UFUNCTION()
	void UpdateMoney();

	AFarmingGameState* GameState;

	APlayerController* PlayerController;

	AFarmer* PlayerCharacter;

	UGameHUDWidget* GameHUD;

	FTimerHandle ClockTimer;

	FClockInfo ClockInfo;

	UFarmingGameInstance* GameInstance;
};
