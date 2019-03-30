// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tool.generated.h"

USTRUCT(BlueprintType)
struct FToolChargeInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TArray<FVector2D> TraceOffsets;
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

private:

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TArray<FToolChargeInfo> AffectedTiles;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 MaxCharge = 0;

	int32 CurrentCharge = 0;
};
