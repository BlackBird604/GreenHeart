// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enums/MovementDirections.h"
#include "Structs/FarmerState.h"
#include "Structs/FatigueInfo.h"
#include "Farmer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UToolInventoryComponent;
class UItemInventoryComponent;
class UAnimSequence;
class UAnimMontage;
class ATool;
class ABed;

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
	void OnHideTool();

	UFUNCTION(BlueprintCallable, Category = "AnimNotifies")
	void OnShowTool();

	UFUNCTION(BlueprintCallable, Category = "AnimNotifies")
	void OnUseToolEnd();

	UFUNCTION(BlueprintCallable, Category = "AnimNotifies")
	void OnToolPreviewEnd();

	UFUNCTION(BlueprintCallable, Category = "AnimNotifies")
	void OnCollectMilk();

	UFUNCTION(BlueprintCallable, Category = "AnimNotifies")
	void OnUseToolStart();

	UFUNCTION(BlueprintCallable, Category = "AnimNotifies")
	void OnItemPack();

	UFUNCTION(BlueprintCallable, Category = "AnimNotifies")
	void OnItemUnpack();

	UFUNCTION(BlueprintCallable, Category = "AnimNotifies")
	void OnSleep();

	UFUNCTION(BlueprintCallable, Category = "AnimNotifies")
	void OnConsume();

	UFUNCTION(BlueprintCallable, Category = "AnimNotifies")
	void OnEatBreakfast();

	UFUNCTION(BlueprintCallable, Category = "AnimNotifies")
	void OnBreakfastEnd();

	UFUNCTION(BlueprintCallable)
	bool HasItemInHands() const;

	void ClearMovementInput();

	void AutomaticMoveTo(TArray<FVector> TargetLocations);

	void AutomaticMoveTo(FVector TargetLocation);

	FFarmerState GetCurrentState();

	void UpdateToolInventory(TArray<FToolInfo> NewToolInfos);

	void UpdateItemInventory(FItemInfo NewItemInHands, TArray<FItemInfo> NewItemInfos);

	bool IsToolInventoryFull();

	void AddTool(const FToolInfo& NewToolInfo);

	void UpgradeToolInventory();

	void UpgradeItemInventory();

	void GoToBed(const FVector& TargetLocation, const FRotator& TargetRotation);

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

	void OnToggleInventory();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USkeletalMeshComponent* BackpackMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UToolInventoryComponent* ToolInventory;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UItemInventoryComponent* ItemInventory;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UAnimMontage* ThrowMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UAnimMontage* ToolPreviewMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TArray<FFatigueInfo> FatigueInfos;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UAnimSequence* OutOfEnergyAnimation;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	FRotator ToolPreviewRotation;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UAnimSequence* BackpackAnimation;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UAnimMontage* PackItemMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UAnimMontage* UnpackItemMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UAnimMontage* BedJumpMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UAnimMontage* BreakfastMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AActor> BreakfastActorClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ChargeDelay = 1.0f;

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

	void UpdateChargePose();

	void ChargeTool();

	UFUNCTION(BlueprintCallable)
	void SetToolHidden(bool bNewHidden);

	void DestroyItemInHands();

	void MoveToNextPoint();

	void UpdateCurrentTool();

	void UpdateFatigueState();

	UPROPERTY()
	ATool* CurrentTool;

	UPROPERTY()
	AActor* ItemInHands;

	UPROPERTY()
	AActor* BreakfastActor;

	TArray<EMovementDirection> MovementInputs;

	bool bIsSprinting = false;

	bool bIsUsingTool = false;

	FTimerHandle ToolChargeTimer;

	TArray<FVector> AutomaticMovementLocations;

	bool bIsAutomaticMovement = false;

	float WalkSpeed = 200.0f;

	float SprintSpeed = 400.0f;

	int32 Energy;

	FRotator SavedRotation = FRotator::ZeroRotator;

	int32 CurrentFatigueState = 0;

	bool bShouldGoToBed = false;

	FRotator BedJumpRotation;
};
