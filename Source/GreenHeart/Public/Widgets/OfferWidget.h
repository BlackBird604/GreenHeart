// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OfferWidget.generated.h"

class UFocusButton;
class UImage;
class UOfferWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOfferClickedSignature, UOfferWidget*, ClickedOffer);

UCLASS()
class GREENHEART_API UOfferWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	bool IsEnabled();

	void SetupFocus();

	FOnOfferClickedSignature OnClicked;

	virtual FText GetOfferName() { return FText(); }

	virtual FText GetOfferDesctiprion() { return FText(); }

	virtual int32 GetOfferPrice() { return 0; }

	virtual UTexture2D* GetThumbnail() { return nullptr; }

	virtual void Buy() {}

	virtual void UpdateActivation();

protected:
	UPROPERTY(meta = (BindWidget))
	UFocusButton* Button;

	UPROPERTY(meta = (BindWidget))
	UImage* Thumbnail;

private:
	UFUNCTION()
	void OnButtonClicked();
};
