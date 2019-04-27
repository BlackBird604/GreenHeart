// The Green Heart @Politechnika Opolska

#pragma once

#include "Enums/AnimalTypes.h"
#include "AnimalOffer.generated.h"

USTRUCT(BlueprintType)
struct FAnimalOffer
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText Name = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText Description = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UTexture2D* Thumbnail = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Cost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EAnimalType AnimalType;
};