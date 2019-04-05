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

protected:
	virtual void BeginPlay() override;

	void OnMoveUpPressed();
	void OnMoveDownPressed();
	void OnMoveLeftPressed();
	void OnMoveRightPressed();
	void OnMoveUpReleased();
	void OnMoveDownReleased();
	void OnMoveLeftReleased();
	void OnMoveRightReleased();

	void OnUseToolPressed();
	void OnUseToolReleased();
	void OnNextToolPressed();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UInventoryComponent* Inventory;

private:

	ATool* SpawnTool();

	void ChargeTool();

	FTimerHandle ToolChargeTimer;

	ATool* CurrentTool;
};
