// The Green Heart @Politechnika Opolska

#pragma once

#include "CoreMinimal.h"
#include "Widgets/OfferWidget.h"
#include "Structs/ConstructionState.h"
#include "ConstructionOfferWidget.generated.h"

class UTextBlock;

UCLASS()
class GREENHEART_API UConstructionOfferWidget : public UOfferWidget
{
	GENERATED_BODY()

public:
	void SetOfferInfo(const FConstructionState& NewOffer);

	FConstructionState GetOfferInfo();

	virtual void UpdateActivation() override;

	virtual void Buy() override;

	virtual FText GetOfferName() override;

	virtual FText GetOfferDesctiprion() override;

	virtual int32 GetOfferPrice() override;

	virtual UTexture2D* GetThumbnail() override;

	FBuildingLevelInfo GetCurrentLevelInfo();

	FBuildingLevelInfo GetNextLevelInfo();

	int32 GetCurrentLevel();

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* NameText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PriceText;

private:
	void SetupWidgetComponents();

	FConstructionState ConstructionOffer;
};
