// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Actors/Others/BaseItem.h"
#include "Interfaces/Sellable.h"
#include "Crop.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class GREENHEART_API ACrop : public ABaseItem, public ISellable
{
	GENERATED_BODY()
	
public:	
	ACrop();

protected:
	virtual void BeginPlay() override;

public:
	virtual int32 GetPrice() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 SellPrice = 0;
};
