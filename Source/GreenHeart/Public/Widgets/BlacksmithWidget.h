// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/BlacksmithInfo.h"
#include "BlacksmithWidget.generated.h"

class UButton;
class UToolOfferWidget;
class UUniformGridPanel;
class UOfferConfirmationWidget;

UCLASS()
class GREENHEART_API UBlacksmithWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	void SetupWidget(const FBlacksmithInfo& NewInfo);

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* UpgradeToolButton;

	UPROPERTY(meta = (BindWidget))
	UButton* UpgradeToolInventoryButton;

	UPROPERTY(meta = (BindWidget))
	UButton* UpgradeItemInventoryButton;

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* OfferGrid;

	UPROPERTY(meta = (BindWidget))
	UOfferConfirmationWidget* OfferConfirmation;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<UToolOfferWidget> OfferClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 OffersInRow = 2;

	UPROPERTY(BlueprintReadWrite, Category = "Animations")
	UWidgetAnimation* ShowOfferConfirmationAnimation;

private:
	void SetupOffers(const TArray<FToolOffer>& Offers);

	void CreateOfferBindings(UToolOfferWidget* OfferWidget);
	
	UFUNCTION()
	void OnOfferClicked(UToolOfferWidget* ClickedOffer);

	UFUNCTION()
	void OnOfferConfirmed();

	UFUNCTION()
	void OnOfferCanceled();
};
