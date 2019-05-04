// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OfferConfirmationWidget.generated.h"

class UImage;
class UTextBlock;
class UFocusButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOfferConfirmedSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOfferCanceledSignature);

UCLASS()
class GREENHEART_API UOfferConfirmationWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

	void SetupFocus();

	void SetOfferName(FText NewName);

	void SetOfferDescription(FText NewDescription);

	void SetOfferPrice(int32 NewPrice);

	void SetOfferThumbnail(UTexture2D* NewTexture);

	FOnOfferConfirmedSignature OnConfirm;

	FOnOfferCanceledSignature OnCancel;

protected:
	UPROPERTY(meta = (BindWidget))
	UFocusButton* ConfirmButton;

	UPROPERTY(meta = (BindWidget))
	UFocusButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	UImage* Thumbnail;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* NameText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DescriptionText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PriceText;

	UFUNCTION()
	virtual void OnConfirmButtonClicked();

private:
	UFUNCTION()
	void OnCancelButtonClicked();
};
