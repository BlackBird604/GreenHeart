// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Structs/ClockInfo.h"
#include "FarmingGameMode.generated.h"

class AFarmingGameState;

UCLASS()
class GREENHEART_API AFarmingGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void StartPlay() override;

	void EndPlay(const EEndPlayReason::Type EndPlayReason);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ClockMinuteTick = 1.0f;

private:
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	void InitializeManagers();

	void InitializeClock();

	void UpdateClock();

	AFarmingGameState* GameState;

	FTimerHandle ClockTimer;

	FClockInfo ClockInfo;
};
