// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/FarmerState.h"
#include "PlayerInventoryWidget.generated.h"

class UUniformGridPanel;
class UInventorySlotWidget;
class UDescriptionWidget;


UCLASS()
class GREENHEART_API UPlayerInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void PopulateSlots(const FFarmerState& FarmerState);

protected:
	UPROPERTY(meta = (BindWidget))
	UInventorySlotWidget* CurrentToolSlot;

	UPROPERTY(meta = (BindWidget))
	UInventorySlotWidget* CurrentItemSlot;

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* ToolGrid;

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* ItemGrid;

	UPROPERTY(meta = (BindWidget))
	UDescriptionWidget* DescriptionBox;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<UInventorySlotWidget> SlotClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 SlotsInRow = 1;

private:
	void PopulateToolSlots(const TArray<FToolInfo>& ToolInfos);

	void PopulateItemSlots(const FItemInfo& ItemInHands, const TArray<FItemInfo>& ToolInfos);
};
