// The Green Heart @Politechnika Opolska

#include "UpgradeConfirmationWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"

bool UUpgradeConfirmationWidget::Initialize()
{
	bool b = Super::Initialize();
	ConfirmButton->OnClicked.AddDynamic(this, &UUpgradeConfirmationWidget::OnConfirmButtonClicked);
	CancelButton->OnClicked.AddDynamic(this, &UUpgradeConfirmationWidget::OnCancelButtonClicked);
	return b;
}

void UUpgradeConfirmationWidget::SetupWidget(const FText& Name, const FLevelInfo& CurrentLevelInfo, const FLevelInfo& NextLevelInfo, int32 CurrentLevel)
{
	NameText->SetText(Name);
	SetLevelText(CurrentLevelText, CurrentLevel);
	SetLevelText(NextLevelText, CurrentLevel + 1);
	SetUpgradePrice(NextLevelInfo.Cost);
	CurrentLevelThumbnail->SetBrushFromTexture(CurrentLevelInfo.Thumbnail);
	NextLevelThumbnail->SetBrushFromTexture(NextLevelInfo.Thumbnail);
}

void UUpgradeConfirmationWidget::SetLevelText(UTextBlock* TextBlock, int32 Level)
{
	FString LevelString = FString::FromInt(Level);
	FText NewText = FText::FromString("Level " + LevelString);
	TextBlock->SetText(NewText);
}

void UUpgradeConfirmationWidget::SetUpgradePrice(int32 NewPrice)
{
	FString PriceString = FString::FromInt(NewPrice);
	FText NewText = FText::FromString(PriceString + "G");
	PriceText->SetText(NewText);
}

void UUpgradeConfirmationWidget::OnConfirmButtonClicked()
{
	OnConfirm.Broadcast();
}

void UUpgradeConfirmationWidget::OnCancelButtonClicked()
{
	OnCancel.Broadcast();
}