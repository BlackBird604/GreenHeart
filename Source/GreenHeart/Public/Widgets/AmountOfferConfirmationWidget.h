// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Widgets/OfferConfirmationWidget.h"
#include "AmountOfferConfirmationWidget.generated.h"

class AFarmingGameMode;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAmountOfferConfirmedSignature, int32, Amount);

UCLASS()
class GREENHEART_API UAmountOfferConfirmationWidget : public UOfferConfirmationWidget
{
	GENERATED_BODY()

public:
	bool Initialize();

	void SetUnitPrice(int32 NewPrice);

	FOnAmountOfferConfirmedSignature OnConfirm;

protected:
	virtual void OnConfirmButtonClicked() override;

	UPROPERTY(meta = (BindWidget))
	UFocusButton* DecreaseAmountButton;

	UPROPERTY(meta = (BindWidget))
	UFocusButton* IncreaseAmountButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AmountText;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 MaxAmount = 999;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AmountUpdateInitialDelay = 0.2f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AmountUpdateRate = 0.05f;

private:
	UFUNCTION()
	void OnIncreaseButtonClicked();
	
	UFUNCTION()
	void OnIncreaseButtonReleased();

	UFUNCTION()
	void OnDecreaseButtonClicked();

	UFUNCTION()
	void OnDecreaseButtonReleased();

	UFUNCTION()
	void IncreaseAmount();

	UFUNCTION()
	void DecreaseAmount();

	void UpdateWidget();

	AFarmingGameMode* GameMode;

	FTimerHandle AmountUpdateTimer;

	int32 CurrentAmount = 1;

	int32 UnitPrice;
};
