// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interfaces/ToolAffectable.h"
#include "Structs/AnimalState.h"
#include "Structs/AnimalItemInfo.h"
#include "Animal.generated.h"

class USceneComponent;
class UBoxComponent;
class USkeletalMeshComponent;
class UPawnMovementComponent;

UCLASS()
class GREENHEART_API AAnimal : public APawn, public IToolAffectable
{
	GENERATED_BODY()

public:
	AAnimal();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void UseTool(const ATool* Instigator, int32 Strength = 0) override;

	virtual void RestoreStateByID(int32 AnimalID) {};

protected:
	void RestoreState(const FAnimalState& AnimalState);

	void RemoveOwnedItem();

	bool HasItem();

	void SetReceivedInteraction();

	virtual void SaveUpdatedState() {}

	TSubclassOf<ABaseItem> GetItemClass();

	FAnimalState GetCurrentState();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USkeletalMeshComponent* AnimalMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnMovementComponent* MovementComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TArray<FAnimalItemInfo> ItemInfos;

private:
	void SetActionTimer(float MinDelay, float MaxDelay);

	UFUNCTION()
	void PerformNextAction();

	bool IsMovementBlocked();

	void Turn();

	FAnimalState CurrentState;

	void ApplyDamage();

	bool bShouldMove = false;

	FTimerHandle ActionTimer;
};
