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
class UAnimalOfferWidget;
class UResourceOfferWidget;
class UOfferConfirmationWidget;
class UAmountOfferConfirmationWidget;
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

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* AnimalGrid;

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* FeedGrid;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<UToolOfferWidget> SeedOfferClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<UAnimalOfferWidget> AnimalOfferClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<UResourceOfferWidget> FeedOfferClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 SeedOffersInRow = 4;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 AnimalOffersInRow = 2;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 FeedOffersInRow = 2;

	UPROPERTY(meta = (BindWidget))
	UOfferConfirmationWidget* OfferConfirmation;

	UPROPERTY(meta = (BindWidget))
	UAmountOfferConfirmationWidget* AmountOfferConfirmation;

	UPROPERTY(BlueprintReadWrite, Category = "Animations")
	UWidgetAnimation* ShowOfferConfirmationAnimation;

	UPROPERTY(BlueprintReadWrite, Category = "Animations")
	UWidgetAnimation* ShowAmountOfferConfirmationAnimation;

private:
	void SetupFocus();

	void CreateConfirmationWidgetBindings();

	void SetupSeedOffers(const TArray<FToolOffer>& Offers);

	void SetupAnimalOffers(const TArray<FAnimalOffer>& Offers);

	void SetupFeedOffers(const TArray<FResourceOffer>& Offers);

	void CreateOfferBindings(UOfferWidget* OfferWidget);

	void CreateAmountOfferBindings(UResourceOfferWidget* OfferWidget);

	UFUNCTION()
	void OnOfferClicked(UOfferWidget* ClickedOffer);

	UFUNCTION()
	void OnAmountOfferClicked(UOfferWidget* ClickedOffer);

	void SetupOfferConfirmationWidget(UOfferWidget* ClickedOffer);

	void SetupAmountOfferConfirmationWidget(UOfferWidget* Offer);

	UFUNCTION()
	void OnOfferConfirmed();

	UFUNCTION()
	void OnAmountOfferConfirmed(int32 Amount);

	UFUNCTION()
	void OnOfferCanceled();

	UFUNCTION()
	void OnAmountOfferCanceled();

	void ShowOfferWidget();

	void HideOfferWidget();

	void ShowAmountOfferWidget();

	void HideAmountOfferWidget();

	void UpdateWidgetState();

	UFUNCTION()
	void CloseWidget();

	void RestoreGame();

	UOfferWidget* ActiveOffer = nullptr;

	TArray<UOfferWidget*> OfferWidgets;

	FSupermarketInfo SupermarketInfo;

};
