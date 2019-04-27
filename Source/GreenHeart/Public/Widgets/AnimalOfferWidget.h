// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Widgets/OfferWidget.h"
#include "Structs/AnimalOffer.h"
#include "AnimalOfferWidget.generated.h"


UCLASS()
class GREENHEART_API UAnimalOfferWidget : public UOfferWidget
{
	GENERATED_BODY()
	
public:
	void SetOfferInfo(const FAnimalOffer& NewOffer);

	FAnimalOffer GetOfferInfo();

	virtual void UpdateActivation() override;

	virtual void Buy() override;

	virtual FText GetOfferName() override;

	virtual FText GetOfferDesctiprion() override;

	virtual int32 GetOfferPrice() override;
	
	virtual UTexture2D* GetThumbnail() override;

private:
	FAnimalOffer AnimalOffer;
};
