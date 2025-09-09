// Copyright (C) 2024 Van de Walle Bastien
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0

#pragma once

#include "CommonButtonBase.h"

#include "ExtendedCommonListItemWidget.generated.h"

struct FExtendedCommonListWidgetItem;

/**
 * Widget to show a list using UCommonHierarchicalScrollBox.
 */
UCLASS(Abstract)
class EXTENDEDCOMMONUI_API UExtendedCommonListItemWidget :
	public UCommonButtonBase
{
	GENERATED_BODY()

	// UCommonButtonBase implementation Begin
public:
	virtual void NativeOnClicked() override;
	virtual void NativeOnHovered() override;
	virtual void NativeOnUnhovered() override;
	// UCommonButtonBase implementation End
	
public:
	void SetItem(int32 InItemID, const FExtendedCommonListWidgetItem& Item);

	DECLARE_EVENT_OneParam(UExtendedCommonListItemWidget, FCommonListItemEvent, int32 /*ID*/);
	FCommonListItemEvent& OnItemSelected() const { return OnItemSelectedEvent; }
	FCommonListItemEvent& OnItemHovered() const { return OnItemHoveredEvent; }
	FCommonListItemEvent& OnItemUnhovered() const { return OnItemUnhoveredEvent; }
	
protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetOptional))
	TObjectPtr<class UCommonRichTextBlock> CommonRichTextBlock_Name;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetOptional))
	TObjectPtr<class UCommonRichTextBlock> CommonRichTextBlock_Description;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetOptional))
	TObjectPtr<class UCommonLazyImage> CommonLazyImage_Icon;

	UPROPERTY(Transient, BlueprintReadOnly)
	int32 ItemID = INDEX_NONE;

protected:
	mutable FCommonListItemEvent OnItemSelectedEvent;
	mutable FCommonListItemEvent OnItemHoveredEvent;
	mutable FCommonListItemEvent OnItemUnhoveredEvent;
};
