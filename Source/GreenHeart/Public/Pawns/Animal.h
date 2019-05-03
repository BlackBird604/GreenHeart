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
class UAnimMontage;
class UWidgetComponent;

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
	UFUNCTION(BlueprintImplementableEvent)
	void OnHit();

	void RestoreState(const FAnimalState& AnimalState);

	void RemoveOwnedItem();

	bool HasItem();

	bool HasReceivedInteraction();

	void SetReceivedInteraction();

	virtual void SaveUpdatedState() {}

	void PlayMessageboxAnimation(bool bIsPositive);

	void PlayMontage(UAnimMontage* MontageToPlay);

	void DisableActions(float Duration);

	TSubclassOf<ABaseItem> GetItemClass();

	FAnimalState GetCurrentState();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* AnimalMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UWidgetComponent* Messagebox;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TArray<FAnimalItemInfo> ItemInfos;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UAnimMontage* HitMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UAnimMontage* InteractionMontage;

private:
	void SetActionTimer(float MinDelay, float MaxDelay);

	UFUNCTION()
	void PerformNextAction();

	bool IsMovementBlocked();

	void Turn();

	FAnimalState CurrentState;

	void ApplyDamage();

	bool IsMontagePlaying();

	bool bShouldMove = false;

	FTimerHandle ActionTimer;
};
