// Copyright (C) 2024 Van de Walle Bastien
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0

#pragma once

#include "ExtendedCommonUserWidget.h"
#include "Interface/ExtendedCommonListWidgetInterface.h"

#include "ExtendedCommonHierarchicalScrollBoxListWidget.generated.h"

/**
 * Widget to show a list using UCommonHierarchicalScrollBox.
 */
UCLASS(Abstract)
class EXTENDEDCOMMONUI_API UExtendedCommonHierarchicalScrollBoxListWidget :
	public UExtendedCommonUserWidget,
	public IExtendedCommonListWidgetInterface
{
	GENERATED_BODY()

	// IExtendedCommonListWidgetInterface implementation Begin
public:
	virtual void SetItems_Implementation(const TArray<FExtendedCommonListWidgetItem>& Items) override;
	virtual void SetItemLocked_Implementation(int32 ItemIndex, bool bLocked) override;
	virtual UWidget* GetItemWidget_Implementation(int32 ItemIndex) const override;
	// IExtendedCommonListWidgetInterface implementation End
	
protected:
	/**
	 * Item widget.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UExtendedCommonListItemWidget> ItemWidgetClass;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonHierarchicalScrollBox> CommonHierarchicalScrollBox_List;

	UFUNCTION()
	void OnItemSelected(int32 ItemIndex);
	
	UFUNCTION()
	void OnItemHovered(int32 ItemIndex);
	
	UFUNCTION()
	void OnItemUnhovered(int32 ItemIndex);
};
