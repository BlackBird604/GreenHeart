// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/ItemInfo.h"
#include "StationaryItemInventoryWidget.generated.h"

class UUniformGridPanel;
class UInventoryItemSlotWidget;
class UDescriptionWidget;
class AFarmer;
class AActor;

UCLASS()
class GREENHEART_API UStationaryItemInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	void SetInventoryActor(AActor* NewInventoryActor);

	void PopulateSlots(AFarmer* Farmer, const TArray<FItemInfo>& StoredItems);

protected:
	UPROPERTY(meta = (BindWidget))
	UInventoryItemSlotWidget* CurrentItemSlot;

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* EquippedItemGrid;

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* StoredItemGrid;

	UPROPERTY(meta = (BindWidget))
	UDescriptionWidget* DescriptionBox;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<UInventoryItemSlotWidget> ItemSlotClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 SlotsInRow = 4;

private:
	void PopulateEquippedItemSlots(const FItemInfo& ItemInHands, const TArray<FItemInfo>& ItemInfos);

	void PopulateStoredItemSlots(const TArray<FItemInfo>& ItemInfos);

	UInventoryItemSlotWidget* GenerateItemSlot(UUniformGridPanel* GridPanel, const FItemInfo& ItemInfo, int32 Index);

	void CreateSlotBindings(UInventoryItemSlotWidget* ItemSlotWidget);

	UFUNCTION()
	void OnItemSlotClicked(UInventorySlotWidget* ClickedSlot);

	UFUNCTION()
	void OnItemSlotHovered(UInventorySlotWidget* HoveredSlot);

	UFUNCTION()
	void OnSlotUnhovered();

	UFUNCTION()
	void CloseWidget();

	void UpdatePlayerInventory();

	void UpdateStationaryInventory();

	void UpdateInventoryActor();

	void RestoreGame();

	TArray<UInventoryItemSlotWidget*> EquippedItemSlots;

	TArray<UInventoryItemSlotWidget*> StoredItemSlots;

	UInventorySlotWidget* ActiveSlot = nullptr;

	AFarmer* PlayerRef;

	AActor* InventoryActor;
};
