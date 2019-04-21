// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/ToolInfo.h"
#include "ToolInventoryComponent.generated.h"

class ATool;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GREENHEART_API UToolInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UToolInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:
	void NextTool();

	FToolInfo GetCurrentTool();

	void RemoveCurrentTool();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TArray<FToolInfo> ToolInfos;

	int32 MinimumSize = 3;
		
};
