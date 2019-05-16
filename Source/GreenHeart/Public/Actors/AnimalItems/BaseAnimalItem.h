// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Actors/Others/BaseItem.h"
#include "Interfaces/Sellable.h"
#include "Interfaces/Consumable.h"
#include "BaseAnimalItem.generated.h"


UCLASS()
class GREENHEART_API ABaseAnimalItem : public ABaseItem, public ISellable, public IConsumable
{
	GENERATED_BODY()

public:
	virtual int32 GetPrice() override;

	virtual int32 GetEnergyPoints() override;
	
	virtual UAnimMontage* GetConsumeMontage() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 SellPrice = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 EnergyPoints = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UAnimMontage* ConsumeMontage;
};
