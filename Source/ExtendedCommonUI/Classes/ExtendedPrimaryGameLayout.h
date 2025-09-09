// Copyright (C) 2024 Van de Walle Bastien
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0

#pragma once

#include "PrimaryGameLayout.h"

#include "ExtendedPrimaryGameLayout.generated.h"

UCLASS(Abstract)
class EXTENDEDCOMMONUI_API UExtendedPrimaryGameLayout : public UPrimaryGameLayout
{
	GENERATED_BODY()

	// UUserWidget implementation Begin
public:
	virtual void NativeConstruct() override;
	// UUserWidget implementation End

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonActivatableWidgetStack> GameLayer_Stack;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonActivatableWidgetStack> GameMenu_Stack;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonActivatableWidgetStack> Menu_Stack;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonActivatableWidgetStack> Modal_Stack;
};
