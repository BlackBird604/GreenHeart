// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Structs/FieldGridState.h"
#include "FarmingGameInstance.generated.h"



UCLASS()
class GREENHEART_API UFarmingGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ApplyNextDay();

	void SetGridState(FFieldGridState NewState);

	FFieldGridState GetGridState();

private:
	UPROPERTY()
	FFieldGridState FieldGridState;
};
