// Copyright (C) 2024 Van de Walle Bastien
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "ExtendedCommonListWidgetInterface.generated.h"

struct FExtendedCommonListWidgetItem;

/**
 * Interface for a generic list widget.
 */
UINTERFACE()
class EXTENDEDCOMMONUI_API UExtendedCommonListWidgetInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class EXTENDEDCOMMONUI_API IExtendedCommonListWidgetInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=ListWidget)
	void SetItems(const TArray<FExtendedCommonListWidgetItem>& Items);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=ListWidget)
	void SetItemLocked(int32 ItemIndex, bool bLocked);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=ListWidget)
	UWidget* GetItemWidget(int32 ItemIndex) const;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FListItemEvent, int32, ItemIndex);
	FListItemEvent& OnItemSelectedEvent() { return OnItemSelectedEventDelegate; };
	FListItemEvent& OnItemHoveredEvent() { return OnItemHoveredEventDelegate; };
	FListItemEvent& OnItemUnhoveredEvent() { return OnItemUnhoveredEventDelegate; };

protected:
	FListItemEvent OnItemSelectedEventDelegate;
	FListItemEvent OnItemHoveredEventDelegate;
	FListItemEvent OnItemUnhoveredEventDelegate;
};
