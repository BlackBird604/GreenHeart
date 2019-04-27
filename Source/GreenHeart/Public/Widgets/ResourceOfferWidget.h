// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Widgets/OfferWidget.h"
#include "Structs/ResourceOffer.h"
#include "ResourceOfferWidget.generated.h"

UCLASS()
class GREENHEART_API UResourceOfferWidget : public UOfferWidget
{
	GENERATED_BODY()
	
public:
	void SetOfferInfo(const FResourceOffer& NewOffer);

	FResourceOffer GetOfferInfo();

	virtual void UpdateActivation() override;

	virtual void Buy() override;

	void Buy(int32 Amount);

	virtual FText GetOfferName() override;

	virtual FText GetOfferDesctiprion() override;

	virtual int32 GetOfferPrice() override;

	virtual UTexture2D* GetThumbnail() override;

private:
	FResourceOffer ResourceOffer;
};
