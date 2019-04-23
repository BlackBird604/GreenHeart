// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NextDayGameMode.generated.h"


UCLASS()
class GREENHEART_API ANextDayGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
};
