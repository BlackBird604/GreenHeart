// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FarmingGameMode.generated.h"


UCLASS()
class GREENHEART_API AFarmingGameMode : public AGameModeBase
{
	GENERATED_BODY()
	

protected:
	virtual void StartPlay() override;

private:
	AActor* ChoosePlayerStart(AController* Player);


};
