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

public:
	int32 Use(const AActor* User);

	bool Charge();

	EToolType GetType() const;

	UAnimMontage* GetChargeMontage();

	UAnimMontage* GetUseMontage();

	bool IsSingleUse();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USkeletalMeshComponent* ToolMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	bool bIsSingleUse = false;

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
