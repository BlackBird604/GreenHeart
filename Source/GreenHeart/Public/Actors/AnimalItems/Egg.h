// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Actors/AnimalItems/BaseAnimalItem.h"
#include "Interfaces/Collectable.h"
#include "Egg.generated.h"

class UBoxComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEggCollectedSignature);

UCLASS()
class GREENHEART_API AEgg : public ABaseAnimalItem, public ICollectable
{
	GENERATED_BODY()
	
public:
	AEgg();

protected:
	virtual void BeginPlay() override;

public:
	virtual bool CanBeCollected() override;

	virtual AActor* Collect() override;

	virtual UAnimMontage* GetPickupMontage() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* InteractionBox;

	FOnEggCollectedSignature OnCollected;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UAnimMontage* PickupMontage;
};
