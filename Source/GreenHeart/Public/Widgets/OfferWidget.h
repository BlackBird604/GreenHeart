// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OfferWidget.generated.h"

class UFocusButton;
class UImage;
class UOfferWidget;
class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOfferHoveredSignature, UOfferWidget*, HoveredOffer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOfferUnhoveredSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOfferClickedSignature, UOfferWidget*, ClickedOffer);

UCLASS()
class GREENHEART_API UOfferWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	bool IsEnabled();

	void SetupFocus();

	FOnOfferHoveredSignature OnHovered;

	FOnOfferUnhoveredSignature OnUnhovered;

	FOnOfferClickedSignature OnClicked;

	virtual FText GetOfferName() { return FText(); }

	virtual FText GetOfferDesctiprion() { return FText(); }

	virtual int32 GetOfferPrice() { return 0; }

	virtual UTexture2D* GetThumbnail() { return nullptr; }

	virtual void Buy() {}

	virtual void UpdateActivation();

protected:
	void SetPriceText(int32 NewPrice);

	UPROPERTY(meta = (BindWidget))
	UFocusButton* Button;

	UPROPERTY(meta = (BindWidget))
	UImage* Thumbnail;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PriceText;

private:
	UFUNCTION()
	void OnButtonHovered();

	UFUNCTION()
	void OnButtonUnhovered();

	UFUNCTION()
	void OnButtonClicked();
};
