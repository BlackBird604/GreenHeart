// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enums/ToolTypes.h"
#include "Structs/ToolInfo.h"
#include "Tool.generated.h"

class UAnimMontage;

USTRUCT(BlueprintType)
struct FToolChargeInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FVector2D> TraceOffsets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAnimMontage* Montage;
};

class USceneComponent;
class USkeletalMeshComponent;

UCLASS()
class GREENHEART_API ATool : public AActor
{
	GENERATED_BODY()
	
public:	
	ATool();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void SetupMaterial(int32 Level);

public:
	void Restore(const FToolInfo& SavedToolInfo);

	virtual int32 Use(const AActor* User);

	bool Charge();

	EToolType GetType() const;

	FToolInfo GetToolInfo();

	UAnimMontage* GetChargeMontage();

	UAnimMontage* GetUseMontage();

	bool IsSingleUse();

	TArray<AActor*> GetAffectedActors();

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnUse(const FVector& GridLocation);

	UFUNCTION(BlueprintImplementableEvent)
	void OnAffectedUse(const FVector& GridLocation);

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* ToolMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	bool bIsSingleUse = false;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	EToolType ToolType;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TArray<FToolChargeInfo> ChargeInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UAnimMontage* UseMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	FToolInfo ToolInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float SequenceUseDelay;

private:
	void PerformInstantUse();

	UFUNCTION()
	void PerformSequenceUse();

	void UseAtLocation(const FVector& Location);

	TArray<FVector> UseLocations;

	TArray<AActor*> AffectedActors;

	FTimerHandle SequenceUseTimer;

	int32 CurrentCharge = 0;
};
