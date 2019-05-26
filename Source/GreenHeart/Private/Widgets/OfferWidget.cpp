// The Green Heart @Politechnika Opolska

#include "OfferWidget.h"
#include "Widgets/Buttons/FocusButton.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "Fundamentals/FarmingGameMode.h"

bool UOfferWidget::Initialize()
{
	bool b = Super::Initialize();
	Button->OnHovered.AddDynamic(this, &UOfferWidget::OnButtonHovered);
	Button->OnUnhovered.AddDynamic(this, &UOfferWidget::OnButtonUnhovered);
	Button->OnClicked.AddDynamic(this, &UOfferWidget::OnButtonClicked);
	Button->StartUpdating();
	return b;
}

bool UOfferWidget::IsEnabled()
{
	return Button->bIsEnabled;
}

void UOfferWidget::SetupFocus()
{
	Button->SetKeyboardFocus();
}

void UOfferWidget::OnButtonHovered()
{
	SetupFocus();
	OnHovered.Broadcast(this);
}

void UOfferWidget::OnButtonUnhovered()
{
	OnUnhovered.Broadcast();
}

void UOfferWidget::OnButtonClicked()
{
	OnClicked.Broadcast(this);
}

void UOfferWidget::UpdateActivation()
{
	if (AFarmingGameMode* GameMode = GetWorld()->GetAuthGameMode<AFarmingGameMode>())
	{
		bool HasResources = GameMode->HasResource(EResourceType::Money, GetOfferPrice());
		Button->SetIsEnabled(HasResources);
	}
}

void UOfferWidget::SetPriceText(int32 NewPrice)
{
	FString PriceString = FString::FromInt(NewPrice);
	FText NewText = FText::FromString(PriceString + "G");
	PriceText->SetText(NewText);
}