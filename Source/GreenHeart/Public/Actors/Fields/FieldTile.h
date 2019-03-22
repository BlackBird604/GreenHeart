// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FieldTile.generated.h"

class UBoxComponent;
class UDecalComponent;
class APlant;

UCLASS()
class GREENHEART_API AFieldTile : public AActor
{
	GENERATED_BODY()
	
public:	
	AFieldTile();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UDecalComponent* Decal;

	UPROPERTY(EditDefaultsOnly, Category = "Temporary")
	TSubclassOf<APlant> PlantClass;

private:
	void SpawnPlant();

	UPROPERTY()
	APlant* PlantActor;

	bool bIsWatered = false;

	bool bIsTilled = false;
};
