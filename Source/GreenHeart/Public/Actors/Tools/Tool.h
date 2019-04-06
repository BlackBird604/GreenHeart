// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

UENUM(BlueprintType)
enum class EToolType : uint8
{
	Hoe,
	WateringCan,
	Seeds
};

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
