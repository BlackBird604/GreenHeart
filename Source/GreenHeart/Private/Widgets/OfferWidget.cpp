// The Green Heart @Politechnika Opolska

#include "OfferWidget.h"
#include "Widgets/Buttons/FocusButton.h"
#include "Components/Image.h"

#include "Fundamentals/FarmingGameMode.h"

bool UOfferWidget::Initialize()
{
	bool b = Super::Initialize();
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