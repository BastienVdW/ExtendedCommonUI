// Copyright (C) 2024 Van de Walle Bastien
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0

#pragma once

#include "Messaging/CommonGameDialog.h"

#include "ExtendedCommonDialog.generated.h"

UCLASS(Abstract)
class EXTENDEDCOMMONUI_API UExtendedCommonDialog : public UCommonGameDialog
{
	GENERATED_BODY()
	
public:
	UExtendedCommonDialog();
	
	virtual void SetupDialog(UCommonGameDialogDescriptor* Descriptor, FCommonMessagingResultDelegate ResultCallback) override;

	virtual void KillDialog() override;

protected:
	virtual void NativeOnInitialized() override;
	virtual void CloseConfirmationWindow(ECommonMessagingResult Result);
	
protected:
	UPROPERTY(EditDefaultsOnly, Category=Dialog)
	TObjectPtr<class UInputAction> ConfirmedInputAction;
	
	UPROPERTY(EditDefaultsOnly, Category=Dialog)
	TObjectPtr<class UInputAction> DeclinedInputAction;
	
	UPROPERTY(EditDefaultsOnly, Category=Dialog)
	TObjectPtr<class UInputAction> CancelledInputAction;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonRichTextBlock> CommonRichTextBlock_Header;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonRichTextBlock> CommonRichTextBlock_Body;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UDynamicEntryBox> EntryBox_Buttons;

private:
	FCommonMessagingResultDelegate OnResultCallback;
};
