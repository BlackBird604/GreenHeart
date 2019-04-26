// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OfferConfirmationWidget.generated.h"

class UButton;
class UImage;
class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConfirmClickedSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCancelClickedSignature);

UCLASS()
class GREENHEART_API UOfferConfirmationWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

	void SetOfferName(FText NewName);

	void SetOfferDescription(FText NewDescription);

	void SetOfferPrice(int32 NewPrice);

	void SetOfferThumbnail(UTexture2D* NewTexture);

	FOnConfirmClickedSignature OnConfirm;

	FOnCancelClickedSignature OnCancel;

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* ConfirmButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	UImage* Thumbnail;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* NameText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DescriptionText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PriceText;

private:
	UFUNCTION()
	void OnConfirmButtonClicked();

	UFUNCTION()
	void OnCancelButtonClicked();

	UFUNCTION()
	void CloseWidget();
};
