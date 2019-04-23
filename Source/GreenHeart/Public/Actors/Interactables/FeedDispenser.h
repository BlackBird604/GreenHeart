// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enums/ResourceTypes.h"
#include "Interfaces/Collectable.h"
#include "FeedDispenser.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class AFeed;
class AFarmingGameState;

UCLASS()
class GREENHEART_API AFeedDispenser : public AActor, public ICollectable
{
	GENERATED_BODY()
	
public:	
	AFeedDispenser();

protected:
	virtual void BeginPlay() override;

public:
	virtual bool CanBeCollected() override;

	virtual AActor* Collect() override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* DispenserMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AFeed> FeedClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	EResourceType ResourceType;

private:
	UPROPERTY()
	AFarmingGameState* GameState;
};
