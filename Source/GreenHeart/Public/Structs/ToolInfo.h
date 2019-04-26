// The Green Heart @Politechnika Opolska

#pragma once

#include "Runtime/CoreUObject/Public/Templates/SubclassOf.h"
#include "ToolInfo.generated.h"

USTRUCT(BlueprintType)
struct FToolInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText Name = FText();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText Description = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class ATool> Class = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* Thumbnail = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Level;
};