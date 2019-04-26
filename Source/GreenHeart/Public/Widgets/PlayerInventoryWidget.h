// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/FarmerState.h"
#include "PlayerInventoryWidget.generated.h"

class UUniformGridPanel;
class UInventoryItemSlotWidget;
class UInventoryToolSlotWidget;
class UDescriptionWidget;
class AFarmer;

UCLASS()
class GREENHEART_API UPlayerInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

	void PopulateSlots(AFarmer* Farmer);

protected:
	UPROPERTY(meta = (BindWidget))
	UInventoryToolSlotWidget* CurrentToolSlot;

	UPROPERTY(meta = (BindWidget))
	UInventoryItemSlotWidget* CurrentItemSlot;

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* ToolGrid;

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* ItemGrid;

	UPROPERTY(meta = (BindWidget))
	UDescriptionWidget* DescriptionBox;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<UInventoryToolSlotWidget> ToolSlotClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<UInventoryItemSlotWidget> ItemSlotClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 SlotsInRow = 4;

private:
	void PopulateToolSlots(const TArray<FToolInfo>& ToolInfos);

	void PopulateItemSlots(const FItemInfo& ItemInHands, const TArray<FItemInfo>& ToolInfos);

	void CreateSlotBindings(UInventoryToolSlotWidget* ToolSlotWidget);

	void CreateSlotBindings(UInventoryItemSlotWidget* ItemSlotWidget);

	UFUNCTION()
	void OnToolSlotClicked(UInventorySlotWidget* ClickedSlot);

	UFUNCTION()
	void OnItemSlotClicked(UInventorySlotWidget* ClickedSlot);

	UFUNCTION()
	void OnToolSlotHovered(UInventorySlotWidget* HoveredSlot);

	UFUNCTION()
	void OnItemSlotHovered(UInventorySlotWidget* HoveredSlot);

	UFUNCTION()
	void OnSlotUnhovered();

	UFUNCTION()
	void CloseWidget();

	void UpdatePlayerInventory();

	void RestoreGame();

	TArray<UInventoryToolSlotWidget*> ToolSlots;

	TArray<UInventoryItemSlotWidget*> ItemSlots;

	UInventorySlotWidget* ActiveSlot = nullptr;

	AFarmer* PlayerRef;
};
