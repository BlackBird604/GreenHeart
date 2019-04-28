// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/ConstructionState.h"
#include "HouseBuilderWidget.generated.h"

class UUniformGridPanel;
class UOfferWidget;
class UConstructionOfferWidget;
class UUpgradeConfirmationWidget;

UCLASS()
class GREENHEART_API UHouseBuilderWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

	void SetupWidget(const TArray<FConstructionState>& NewConstructionStates);

protected:
	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* OfferGrid;

	UPROPERTY(meta = (BindWidget))
	UUpgradeConfirmationWidget* UpgradeConfirmation;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<UConstructionOfferWidget> ConstructionOfferClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 OffersInRow = 1;

	UPROPERTY(BlueprintReadWrite, Category = "Animations")
	UWidgetAnimation* ShowUpgradeConfirmationAnimation;

private:
	void CreateConfirmationWidgetBindings();

	void SetupConstructionOffers(const TArray<FConstructionState>& Offers);

	void CreateOfferBindings(UOfferWidget* OfferWidget);

	UFUNCTION()
	void OnOfferClicked(UOfferWidget* ClickedOffer);

	void SetupUpgradeConfirmationWidget(UConstructionOfferWidget* ClickedOffer);

	UFUNCTION()
	void OnUpgradeConfirmed(int32 Price);

	UFUNCTION()
	void OnUpgradeCanceled();

	UFUNCTION()
	void CloseWidget();

	void RestoreGame();

	void ShowUpgradeConfirmationWidget();

	void HideUpgradeConfirmationWidget();

	UConstructionOfferWidget* ActiveOffer = nullptr;

	TArray<UConstructionOfferWidget*> OfferWidgets;
};
