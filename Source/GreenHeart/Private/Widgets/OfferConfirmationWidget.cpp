// The Green Heart @Politechnika Opolska

#include "OfferConfirmationWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"

bool UOfferConfirmationWidget::Initialize()
{
	bool b = Super::Initialize();
	ConfirmButton->OnClicked.AddDynamic(this, &UOfferConfirmationWidget::OnConfirmButtonClicked);
	CancelButton->OnClicked.AddDynamic(this, &UOfferConfirmationWidget::OnCancelButtonClicked);
	return b;
}

void UOfferConfirmationWidget::SetOfferName(FText NewName)
{
	NameText->SetText(NewName);
}

void UOfferConfirmationWidget::SetOfferDescription(FText NewDescription)
{
	DescriptionText->SetText(NewDescription);
}

void UOfferConfirmationWidget::SetOfferPrice(int32 NewPrice)
{
	FString PriceString = FString::FromInt(NewPrice);
	FText NewText = FText::FromString(PriceString + "G");
	PriceText->SetText(NewText);
}

void UOfferConfirmationWidget::SetOfferThumbnail(UTexture2D* NewTexture)
{
	Thumbnail->SetBrushFromTexture(NewTexture);
}

void UOfferConfirmationWidget::OnConfirmButtonClicked()
{
	OnConfirm.Broadcast();
}

void UOfferConfirmationWidget::OnCancelButtonClicked()
{
	OnCancel.Broadcast();
}