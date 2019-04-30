// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "Enums/StationaryInventoryTypes.h"
#include "StationaryInventory.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class GREENHEART_API AStationaryInventory : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	AStationaryInventory();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Interact() override;

	void EndInteraction();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* InventoryMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	EStationaryInventoryType InventoryType;

	UFUNCTION(BlueprintImplementableEvent)
	void OnInteractionStart();

	UFUNCTION(BlueprintImplementableEvent)
	void OnInteractionEnd();
};
