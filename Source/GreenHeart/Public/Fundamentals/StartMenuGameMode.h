// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StartMenuGameMode.generated.h"

class UStartMenuWidget;

UCLASS()
class GREENHEART_API AStartMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup|UMG")
	TSubclassOf<UStartMenuWidget> StartMenuWidgetClass;

private:
	void EnableUIMode();
};
