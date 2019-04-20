// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enums/ToolTypes.h"
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

public:
	void Use(const AActor* User);

	bool Charge();

	EToolType GetType() const;

	UAnimMontage* GetChargeMontage();

	UAnimMontage* GetUseMontage();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USkeletalMeshComponent* ToolMesh;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	EToolType ToolType;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TArray<FToolChargeInfo> ChargeInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UAnimMontage* UseMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 MaxCharge = 0;

	int32 CurrentCharge = 0;
};
