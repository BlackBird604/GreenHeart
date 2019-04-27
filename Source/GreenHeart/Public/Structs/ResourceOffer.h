// The Green Heart @Politechnika Opolska

#pragma once

#include "Enums/ResourceTypes.h"
#include "ResourceOffer.generated.h"

USTRUCT(BlueprintType)
struct FResourceOffer
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
	EResourceType ResourceType;
};