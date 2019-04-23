// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "FarmerSpawnPoint.generated.h"


UCLASS()
class GREENHEART_API AFarmerSpawnPoint : public APlayerStart
{
	GENERATED_BODY()
	
public:
	int32 GetID();

protected:
	UPROPERTY(EditAnywhere, Category = "Setup")
	int32 ID = 0;
};
