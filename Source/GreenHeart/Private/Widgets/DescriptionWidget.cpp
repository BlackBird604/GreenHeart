// The Green Heart @Politechnika Opolska

#include "DescriptionWidget.h"
#include "Components/TextBlock.h"

bool UDescriptionWidget::Initialize()
{
	bool b = Super::Initialize();
	ClearText();
	return b;
}

void UDescriptionWidget::SetText(FText NewName, FText NewDescription)
{
	if (NameText && DescriptionText)
	{
		NameText->SetText(NewName);
		DescriptionText->SetText(NewDescription);
	}
}

void UDescriptionWidget::ClearText()
{
	if (NameText && DescriptionText)
	{
		NameText->SetText(FText());
		DescriptionText->SetText(FText());
	}
}

