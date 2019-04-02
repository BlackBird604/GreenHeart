// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class ATool;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GREENHEART_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:
	void NextTool();

	TSubclassOf<ATool> GetCurrentTool();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TArray<TSubclassOf<ATool>> Tools;
		
};
