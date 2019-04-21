// The Green Heart @Politechnika Opolska

#pragma once

#include "ToolInfo.generated.h"

USTRUCT(BlueprintType)
struct FToolInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class ATool> Class;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Level;
};