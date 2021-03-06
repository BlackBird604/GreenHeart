// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Actors/Others/BaseItem.h"
#include "Interfaces/Sellable.h"
#include "Interfaces/Consumable.h"
#include "Crop.generated.h"

UCLASS()
class GREENHEART_API ACrop : public ABaseItem, public ISellable, public IConsumable
{
	GENERATED_BODY()
	
public:	
	ACrop();

protected:
	virtual void BeginPlay() override;

public:
	virtual int32 GetPrice() override;

	virtual int32 GetEnergyPoints() override;

	virtual UAnimMontage* GetConsumeMontage() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 SellPrice = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 EnergyPoints = 0;

	UPROPERTY(EditDefaultsOnly,Category = "Setup")
	UAnimMontage* ConsumeMontage;
};
