// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "Door.generated.h"

class UBoxComponent;
class USceneComponent;

UCLASS()
class GREENHEART_API ADoor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	ADoor();

	virtual void Interact() override;

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* FirstMovementPoint;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* SecondMovementPoint;
};
