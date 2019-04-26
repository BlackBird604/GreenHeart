// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/ToolInventoryState.h"
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
	FToolInventoryState GetState();

	void RestoreState(FToolInventoryState InventoryState);

	void NextTool();

	FToolInfo GetCurrentTool();

	void RemoveCurrentTool();

	void Update(TArray<FToolInfo> NewToolInfos);

	bool HasPlace();

	void InsertNewTool(const FToolInfo& NewToolInfo);

private:
	void RestoreSize(int32 Level);

	void RestoreTools(const TArray<FToolInfo>& SavedToolInfos);

	TArray<FToolInfo> ToolInfos;

	int32 CurrentLevel;
		
};
