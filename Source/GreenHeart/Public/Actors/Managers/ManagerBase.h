// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ManagerBase.generated.h"

UCLASS()
class GREENHEART_API AManagerBase : public AActor
{
	GENERATED_BODY()
	
public:
	virtual void StartPlay() {};

};
