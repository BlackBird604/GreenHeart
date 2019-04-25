// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Structs/ClockInfo.h"
#include "FarmingGameMode.generated.h"

class AFarmingGameState;
class UGameHUDWidget;
class UPlayerInventoryWidget;
class APlayerController;
class AFarmer;

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
	void TogglePlayerInventory();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup|UMG")
	TSubclassOf<UGameHUDWidget> GameHUDClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup|UMG")
	TSubclassOf<UPlayerInventoryWidget> PlayerInventoryWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ClockMinuteTick = 1.0f;

private:
	void CreateHUD();

	void InitializeManagers();

	void InitializeClockWidget();

	void UpdateClock();

	UFUNCTION()
	void UpdateMoney();

	AFarmingGameState* GameState;

	APlayerController* PlayerController;

	AFarmer* PlayerCharacter;

	UGameHUDWidget* GameHUD;

	UPlayerInventoryWidget* PlayerInventoryWidget;

	FTimerHandle ClockTimer;

	FClockInfo ClockInfo;
};
