// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Farmer.generated.h"

UENUM(BlueprintType)
enum class EMovementDirection : uint8
{
	Up,
	Down,
	Left,
	Right
};

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

	void OnSprintPressed();

	UFUNCTION(BlueprintCallable, Category = "AnimNotifies")
	void SetToolHidden(bool bNewHidden);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void PlayPickupTimeline();

	void OnMoveUpPressed();
	void OnMoveDownPressed();
	void OnMoveLeftPressed();
	void OnMoveRightPressed();
	void OnMoveUpReleased();
	void OnMoveDownReleased();
	void OnMoveLeftReleased();
	void OnMoveRightReleased();

	void OnSprintReleased();

	void OnUseToolPressed();
	void OnUseToolReleased();
	void OnNextToolPressed();
	void OnInteractPressed();
	void OnNextItemPressed();

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
	bool ShouldMove();

	bool IsMontagePlaying();

	void UpdateRotation();

	AActor* GetActorByTraceChannel(ECollisionChannel CollisionChannel);

	ATool* SpawnTool();

	AActor* GetItemFromInventory();

	void UpdateChargePose();

	void ChargeTool();

	bool bIsSprinting = false;

	bool bIsUsingTool = false;

	FTimerHandle ToolChargeTimer;

	UPROPERTY()
	ATool* CurrentTool;

	UPROPERTY()
	AActor* ItemInHands;

	TArray<EMovementDirection> MovementInputs;
};
