// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Structs/ClockInfo.h"
#include "FarmingGameMode.generated.h"

class AFarmingGameState;
class UGameHUDWidget;

UCLASS()
class GREENHEART_API AFarmingGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void AddMoney(int32 Amount);

protected:
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	virtual void BeginPlay() override;

	virtual void StartPlay() override;

	void EndPlay(const EEndPlayReason::Type EndPlayReason);

	UPROPERTY(EditDefaultsOnly, Category = "Setup|UMG")
	TSubclassOf<UGameHUDWidget> GameHUDClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ClockMinuteTick = 1.0f;

private:
	void CreateHUD();

	void InitializeManagers();

	void InitializeClockWidget();

	void UpdateClock();

	AFarmingGameState* GameState;

	UGameHUDWidget* GameHUD;

	FTimerHandle ClockTimer;

	FClockInfo ClockInfo;
};
