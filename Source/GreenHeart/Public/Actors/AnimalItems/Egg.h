// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Actors/Others/BaseItem.h"
#include "Interfaces/Sellable.h"
#include "Interfaces/Consumable.h"
#include "Interfaces/Collectable.h"
#include "Egg.generated.h"

class UBoxComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEggCollectedSignature);

UCLASS()
class GREENHEART_API AEgg : public ABaseItem, public ISellable, public IConsumable, public ICollectable
{
	GENERATED_BODY()
	
public:
	AEgg();

protected:
	virtual void BeginPlay() override;

public:
	virtual int32 GetPrice() override;

	virtual int32 GetEnergyPoints() override;

	virtual bool CanBeCollected() override;

	virtual AActor* Collect() override;

	virtual UAnimMontage* GetPickupMontage() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* InteractionBox;

	FOnEggCollectedSignature OnCollected;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 SellPrice = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 EnergyPoints = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UAnimMontage* PickupMontage;
};
