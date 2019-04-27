// The Green Heart @Politechnika Opolska

#include "OfferWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"

#include "Fundamentals/FarmingGameMode.h"

bool UOfferWidget::Initialize()
{
	bool b = Super::Initialize();
	Button->OnClicked.AddDynamic(this, &UOfferWidget::OnButtonClicked);
	return b;
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