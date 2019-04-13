// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Farmer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInventoryComponent;
class ATool;

UCLASS()
class GREENHEART_API AFarmer : public ACharacter
{
	GENERATED_BODY()

public:
	AFarmer();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move();

	void OnSprintPressed();

	UFUNCTION(BlueprintCallable, Category = "AnimNotifies")
	void DisableMovement();

	UFUNCTION(BlueprintCallable, Category = "AnimNotifies")
	void EnableMovement();

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

	// Temporary
	void OnResetLevelPressed();
	void OnNextDayPressed();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UInventoryComponent* Inventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* PickupComponent;

private:
	ATool* SpawnTool();

	void UpdateChargePose();

	void ChargeTool();

	FTimerHandle ToolChargeTimer;

	ATool* CurrentTool;

	AActor* ItemInHands;
};
