// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ItemInteractable.h"
#include "Structs/FeedBoxState.h"
#include "FeedBox.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class AFeed;

UCLASS()
class GREENHEART_API AFeedBox : public AActor, public IItemInteractable
{
	GENERATED_BODY()
	
public:	
	AFeedBox();

protected:
	virtual void BeginPlay() override;

public:	
	int32 GetID();

	FFeedBoxState GetState();

	void RestoreState(FFeedBoxState BoxState);

	virtual bool CanInteract(AActor* Item) override;

	virtual void Interact(AActor* Item) override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* BoxMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* FeedMesh;

	UPROPERTY(EditAnywhere, Category = "Setup")
	int32 ID;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AFeed> AcceptedFeedClass;

private:
	bool bHasFeed = false;
};
