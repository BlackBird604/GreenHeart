// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/ToolOffer.h"
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

	void SetOffer(const FToolOffer& NewOffer);

	FOnOfferClickedSignature OnClicked;

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* Button;

	UPROPERTY(meta = (BindWidget))
	UImage* Thumbnail;

private:
	UFUNCTION()
	void OnButtonClicked();

	void SetThumbnail(TSubclassOf<ATool> ToolClass);

	FToolOffer ToolOffer;
};
