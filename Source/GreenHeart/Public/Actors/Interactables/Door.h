// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "Door.generated.h"

class USceneComponent;
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
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void PlayOpenTimeline();

	UFUNCTION(BlueprintCallable)
	void OnClosed();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* PawnBlockingVolume;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* FirstMovementPoint;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* SecondMovementPoint;
};
