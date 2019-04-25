// The Green Heart @Politechnika Opolska

#pragma once

#include "ToolInfo.generated.h"

USTRUCT(BlueprintType)
struct FToolInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class ATool> Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* Thumbnail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Level;
};