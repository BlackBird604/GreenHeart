// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/ToolOffer.h"
#include "Structs/SupermarketInfo.h"
#include "SupermarketWidget.generated.h"

class UUniformGridPanel;
class UOfferWidget;
class UToolOfferWidget;
class UOfferConfirmationWidget;
class UWidgetAnimation;

UCLASS()
class GREENHEART_API USupermarketWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

	void SetupWidget(const FSupermarketInfo& NewSupermarketInfo);

protected:
	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* SeedGrid;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<UToolOfferWidget> SeedOfferClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 OffersInRow = 4;

	UPROPERTY(meta = (BindWidget))
	UOfferConfirmationWidget* OfferConfirmation;

	UPROPERTY(BlueprintReadWrite, Category = "Animations")
	UWidgetAnimation* ShowOfferConfirmationAnimation;

private:
	void CreateConfirmationWidgetBindings();

	void SetupOffers(const TArray<FToolOffer>& Offers);

	void CreateOfferBindings(UToolOfferWidget* OfferWidget);

	UFUNCTION()
	void OnOfferClicked(UOfferWidget* ClickedOffer);

	void SetupOfferConfirmationWidget(UOfferWidget* ClickedOffer);

	UFUNCTION()
	void OnOfferConfirmed();

	UFUNCTION()
	void OnOfferCanceled();

	void ShowOfferWidget();

	void HideOfferWidget();

	void UpdateWidgetState();

	UFUNCTION()
	void CloseWidget();

	void RestoreGame();

	UOfferWidget* ActiveOffer = nullptr;

	TArray<UToolOfferWidget*> OfferWidgets;

	FSupermarketInfo SupermarketInfo;

};
