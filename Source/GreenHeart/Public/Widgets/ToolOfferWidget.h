// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/ToolOffer.h"
#include "Structs/ToolInfo.h"
#include "ToolOfferWidget.generated.h"

class UButton;
class UImage;
class UToolOfferWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOfferClickedSignature, UToolOfferWidget*, ClickedOffer);

UCLASS()
class GREENHEART_API UToolOfferWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

	void SetOfferInfo(const FToolOffer& NewOffer);

	FToolOffer GetOfferInfo();

	void UpdateActivation();

	void SetAvailability(bool bNewAvalable);

	void Buy();

	FOnOfferClickedSignature OnClicked;

	FText GetOfferName();

	FText GetOfferDesctiprion();

	int32 GetOfferPrice();

	UTexture2D* GetThumbnail();

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* Button;

	UPROPERTY(meta = (BindWidget))
	UImage* Thumbnail;

private:
	UFUNCTION()
	void OnButtonClicked();

	void SetDefaults(TSubclassOf<class ATool> ToolClass);

	FToolOffer ToolOffer;

	FToolInfo ToolInfo;

	UTexture2D* OfferThumbnail;

	int32 OfferPrice;
};
