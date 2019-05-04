// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotWidget.generated.h"


class UFocusButton;
class UImage;
class UInventorySlotWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotClickedSignature, UInventorySlotWidget*, ClickedSlot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotHoveredSignature, UInventorySlotWidget*, HoveredSlot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSlotUnhoveredSignature);

UCLASS()
class GREENHEART_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	bool Initialize();

public:
	FOnSlotClickedSignature OnClicked;

	FOnSlotHoveredSignature OnHovered;

	FOnSlotUnhoveredSignature OnUnhovered;

	void SetupFocus();

protected:
	void SetThumbnail(UTexture2D* NewTexture);

	UPROPERTY(meta = (BindWidget))
	UFocusButton* Button;

	UPROPERTY(meta = (BindWidget))
	UImage* Thumbnail;

private:
	UFUNCTION()
	void OnButtonClicked();

	UFUNCTION()
	void OnButtonHovered();

	UFUNCTION()
	void OnButtonUnhovered();
};

