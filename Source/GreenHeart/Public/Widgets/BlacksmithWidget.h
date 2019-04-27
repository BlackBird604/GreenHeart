// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/BlacksmithInfo.h"
#include "Structs/FarmerState.h"
#include "BlacksmithWidget.generated.h"

class UButton;
class UImage;
class UToolOfferWidget;
class UUniformGridPanel;
class UOfferConfirmationWidget;
class UUpgradeConfirmationWidget;

UCLASS()
class GREENHEART_API UBlacksmithWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	void SetupWidget(const FFarmerState& NewFarmerState, const FBlacksmithInfo& NewBlacksmithInfo);

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* UpgradeToolButton;

	UPROPERTY(meta = (BindWidget))
	UButton* UpgradeToolInventoryButton;

	UPROPERTY(meta = (BindWidget))
	UButton* UpgradeItemInventoryButton;

	UPROPERTY(meta = (BindWidget))
	UImage* ToolIcon;

	UPROPERTY(meta = (BindWidget))
	UImage* ToolInventoryIcon;

	UPROPERTY(meta = (BindWidget))
	UImage* ItemInventoryIcon;

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* OfferGrid;

	UPROPERTY(meta = (BindWidget))
	UOfferConfirmationWidget* OfferConfirmation;

	UPROPERTY(meta = (BindWidget))
	UUpgradeConfirmationWidget* UpgradeConfirmation;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<UToolOfferWidget> OfferClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 OffersInRow = 2;

	UPROPERTY(BlueprintReadWrite, Category = "Animations")
	UWidgetAnimation* ShowOfferConfirmationAnimation;

	UPROPERTY(BlueprintReadWrite, Category = "Animations")
	UWidgetAnimation* ShowUpgradeConfirmationAnimation;

private:
	void CreateConfirmationWidgetBindings();

	void SetupOffers(const TArray<FToolOffer>& Offers);

	void CreateUpgradeButtonBindings();

	void SetupUpgrades();

	void SetupToolUpgrade();

	void SetupToolInventoryUpgrade();

	void SetupItemInventoryUpgrade();

	void CreateOfferBindings(UToolOfferWidget* OfferWidget);
	
	UFUNCTION()
	void CloseWidget();

	void SaveBlacksmithInfo();

	void ShowOfferWidget();

	void HideOfferWidget();

	void ShowUpgradeWidget();

	void HideUpgradeWidget();

	void RestoreGame();

	UFUNCTION()
	void OnOfferClicked(UToolOfferWidget* ClickedOffer);

	UFUNCTION()
	void OnToolUpgradeClicked();

	UFUNCTION()
	void OnToolInventoryUpgradeClicked();

	UFUNCTION()
	void OnItemInventoryUpgradeClicked();

	UFUNCTION()
	void OnOfferConfirmed();

	UFUNCTION()
	void OnOfferCanceled();

	UFUNCTION()
	void OnUpgradeConfirmed();

	UFUNCTION()
	void OnUpgradeCanceled();

	TArray<UToolOfferWidget*> OfferWidgets;

	UToolOfferWidget* ActiveOffer = nullptr;

	FBlacksmithInfo BlacksmithInfo;

	FFarmerState FarmerState;

	UButton* ClickedUpgradeButton = nullptr;
};
