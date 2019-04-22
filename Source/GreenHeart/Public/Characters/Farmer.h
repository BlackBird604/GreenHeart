// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enums/MovementDirections.h"
#include "Structs/FarmerState.h"
#include "Farmer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UToolInventoryComponent;
class UItemInventoryComponent;
class ATool;

UCLASS()
class GREENHEART_API AFarmer : public ACharacter
{
	GENERATED_BODY()

public:
	AFarmer();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UFUNCTION(BlueprintCallable, Category = "AnimNotifies")
	void OnUseToolEnd();

	void AddMoney(int32 Amount);

	void AutomaticMoveTo(TArray<FVector> TargetLocations);

	void AutomaticMoveTo(FVector TargetLocation);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void PlayPickupTimeline();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void PlayMovementTimeline(float Duration);

	UFUNCTION(BlueprintCallable)
	void OnMovementTimelineFinished();

	void OnMoveUpPressed();
	void OnMoveDownPressed();
	void OnMoveLeftPressed();
	void OnMoveRightPressed();
	void OnMoveUpReleased();
	void OnMoveDownReleased();
	void OnMoveLeftReleased();
	void OnMoveRightReleased();

	void OnSprintPressed();
	void OnSprintReleased();

	void OnUseToolPressed();
	void OnUseToolReleased();
	void OnNextToolPressed();
	void OnInteractPressed();
	void OnNextItemPressed();
	void OnEatPressed();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UToolInventoryComponent* ToolInventory;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UItemInventoryComponent* ItemInventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* PickupComponent;

private:
	void SaveState();

	void RestoreState();

	void RestoreItemInHands(TSubclassOf<AActor> ItemClass);

	bool ShouldMove();

	void SetSprint(bool bActive);

	void StartAutomaticMovement();

	void EndAutomaticMovement();

	bool IsMontagePlaying();

	void UpdateRotation();

	FRotator GetLookAtXYRotation(const FVector& TargetLocation);

	AActor* GetActorByTraceChannel(ECollisionChannel CollisionChannel);

	void AttachActorToItemSocket(AActor* Item);

	ATool* SpawnTool();

	AActor* GetItemFromInventory();

	void UpdateChargePose();

	void ChargeTool();

	void SetToolHidden(bool bNewHidden);

	void DestroyItemInHands();

	void MoveToNextPoint();

	UPROPERTY()
	ATool* CurrentTool;

	UPROPERTY()
	AActor* ItemInHands;

	TArray<EMovementDirection> MovementInputs;

	bool bIsSprinting = false;

	bool bIsUsingTool = false;

	FTimerHandle ToolChargeTimer;

	TArray<FVector> AutomaticMovementLocations;

	bool bIsAutomaticMovement = false;

	float WalkSpeed = 200.0f;

	float SprintSpeed = 400.0f;

	int32 Energy;

	int32 MoneyAmount;
};
