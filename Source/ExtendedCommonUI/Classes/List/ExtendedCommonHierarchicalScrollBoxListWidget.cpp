// Copyright (C) 2024 Van de Walle Bastien
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0


#include "ExtendedCommonHierarchicalScrollBoxListWidget.h"

#include "CommonHierarchicalScrollBox.h"
#include "ExtendedCommonListItemWidget.h"
#include "Interface/ExtendedCommonListWidgetTypes.h"

void UExtendedCommonHierarchicalScrollBoxListWidget::SetItems_Implementation(
	const TArray<FExtendedCommonListWidgetItem>& Items)
{
	if (CommonHierarchicalScrollBox_List && ItemWidgetClass)
	{
		CommonHierarchicalScrollBox_List->ClearChildren();
		
		for (int32 ItemIndex = 0; ItemIndex < Items.Num(); ItemIndex++)
		{
			const FExtendedCommonListWidgetItem& Item = Items[ItemIndex];
			
			UExtendedCommonListItemWidget* ItemWidget = CreateWidget<UExtendedCommonListItemWidget>(GetOwningPlayer(), ItemWidgetClass);
			if (IsValid(ItemWidget))
			{
				ItemWidget->SetItem(ItemIndex, Item);
				ItemWidget->SetIsLocked(Item.bLocked);
				ItemWidget->OnItemSelected().RemoveAll(this);
				ItemWidget->OnItemSelected().AddUObject(this, &ThisClass::OnItemSelected);
				ItemWidget->OnItemHovered().AddUObject(this, &ThisClass::OnItemHovered);
				ItemWidget->OnItemUnhovered().AddUObject(this, &ThisClass::OnItemUnhovered);
				CommonHierarchicalScrollBox_List->AddChild(ItemWidget);
			}
		}

		SetIsFocusable(true);
		SetDesiredFocusWidget(CommonHierarchicalScrollBox_List->GetChildAt(0));
	}
}

void UExtendedCommonHierarchicalScrollBoxListWidget::SetItemLocked_Implementation(int32 ItemIndex, bool bLocked)
{
	if (UExtendedCommonListItemWidget* ItemWidget = Cast<UExtendedCommonListItemWidget>(
		CommonHierarchicalScrollBox_List->GetChildAt(ItemIndex)))
	{
		ItemWidget->SetIsLocked(bLocked);
	}
}

UWidget* UExtendedCommonHierarchicalScrollBoxListWidget::GetItemWidget_Implementation(int32 ItemIndex) const
{
	if (CommonHierarchicalScrollBox_List)
	{
		return CommonHierarchicalScrollBox_List->GetChildAt(ItemIndex);
	}
	else
	{		
		return nullptr;
	}
}

void UExtendedCommonHierarchicalScrollBoxListWidget::OnItemSelected(int32 ItemIndex)
{
	OnItemSelectedEventDelegate.Broadcast(ItemIndex);
}

void UExtendedCommonHierarchicalScrollBoxListWidget::OnItemHovered(int32 ItemIndex)
{
	OnItemHoveredEventDelegate.Broadcast(ItemIndex);
}

void UExtendedCommonHierarchicalScrollBoxListWidget::OnItemUnhovered(int32 ItemIndex)
{
	OnItemUnhoveredEventDelegate.Broadcast(ItemIndex);
}
