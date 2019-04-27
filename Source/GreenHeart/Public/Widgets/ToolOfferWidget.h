// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Widgets/OfferWidget.h"
#include "Structs/ToolOffer.h"
#include "Structs/ToolInfo.h"
#include "ToolOfferWidget.generated.h"

UCLASS()
class GREENHEART_API UToolOfferWidget : public UOfferWidget
{
	GENERATED_BODY()
	
public:
	void SetOfferInfo(const FToolOffer& NewOffer);

	FToolOffer GetOfferInfo();

	void SetAvailability(bool bNewAvalable);

	virtual void UpdateActivation() override;

	virtual void Buy() override;

	virtual FText GetOfferName() override;

	virtual FText GetOfferDesctiprion() override;

	virtual int32 GetOfferPrice() override;

	virtual UTexture2D* GetThumbnail() override;

private:
	void SetDefaults(TSubclassOf<class ATool> ToolClass);

	FToolOffer ToolOffer;

	FToolInfo ToolInfo;

	UTexture2D* OfferThumbnail;

	int32 OfferPrice;
};
