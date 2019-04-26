// The Green Heart @Politechnika Opolska

#include "ToolOfferWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"

#include "Actors/Tools/Tool.h"

bool UToolOfferWidget::Initialize()
{
	bool b = Super::Initialize();
	Button->OnClicked.AddDynamic(this, &UToolOfferWidget::OnButtonClicked);
	return b;
}

void UToolOfferWidget::SetOffer(const FToolOffer& NewOffer)
{
	ToolOffer = NewOffer;
	SetThumbnail(ToolOffer.OfferedClass);
}

void UToolOfferWidget::SetThumbnail(TSubclassOf<ATool> ToolClass)
{
	if (ToolClass)
	{
		ATool* DefaultTool = Cast<ATool>(ToolClass->GetDefaultObject());
		if (DefaultTool)
		{
			UTexture2D* ToolIcon = DefaultTool->GetToolInfo().Thumbnail;
			Thumbnail->SetBrushFromTexture(ToolIcon);
		}
	}
}

void UToolOfferWidget::OnButtonClicked()
{
	OnClicked.Broadcast(this);
}