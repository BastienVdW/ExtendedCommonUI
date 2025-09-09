// Copyright (C) 2024 Van de Walle Bastien
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0


#include "ExtendedCommonListItemWidget.h"

#include "CommonLazyImage.h"
#include "CommonRichTextBlock.h"
#include "Interface/ExtendedCommonListWidgetTypes.h"

void UExtendedCommonListItemWidget::NativeOnClicked()
{
	Super::NativeOnClicked();

	if (!GetLocked())
	{
		OnItemSelectedEvent.Broadcast(ItemID);
	}
}

void UExtendedCommonListItemWidget::NativeOnHovered()
{
	Super::NativeOnHovered();
	
	OnItemHoveredEvent.Broadcast(ItemID);
}

void UExtendedCommonListItemWidget::NativeOnUnhovered()
{
	Super::NativeOnUnhovered();
	
	OnItemUnhoveredEvent.Broadcast(ItemID);
}

void UExtendedCommonListItemWidget::SetItem(int32 InItemID, const FExtendedCommonListWidgetItem& Item)
{
	ItemID = InItemID;
	
	if (CommonRichTextBlock_Name)
	{
		CommonRichTextBlock_Name->SetText(Item.LocalizedName);
	}

	if (CommonRichTextBlock_Description)
	{
		CommonRichTextBlock_Description->SetText(Item.LocalizedDescription);
	}

	if (CommonLazyImage_Icon)
	{
		CommonLazyImage_Icon->SetBrushFromLazyTexture(Item.IconTexture);
	}
}
