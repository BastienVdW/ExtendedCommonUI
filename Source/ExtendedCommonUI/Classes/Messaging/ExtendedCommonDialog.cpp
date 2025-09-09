// Copyright (C) 2024 Van de Walle Bastien
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0


#include "ExtendedCommonDialog.h"

#include "CommonRichTextBlock.h"
#include "Components/DynamicEntryBox.h"
#include "ExtendedCommonButtonBase.h"

UExtendedCommonDialog::UExtendedCommonDialog()
	: Super()
{
}

void UExtendedCommonDialog::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UExtendedCommonDialog::SetupDialog(UCommonGameDialogDescriptor* Descriptor,
                                        FCommonMessagingResultDelegate ResultCallback)
{
	Super::SetupDialog(Descriptor, ResultCallback);

	if (CommonRichTextBlock_Header)
	{
		CommonRichTextBlock_Header->SetText(Descriptor->Header);
	}

	if (CommonRichTextBlock_Body)
	{
		CommonRichTextBlock_Body->SetText(Descriptor->Body);
	}

	if (EntryBox_Buttons)
	{
		EntryBox_Buttons->Reset<UExtendedCommonButtonBase>([](UExtendedCommonButtonBase& Button)
		{
			Button.OnClicked().Clear();
		});

		for (const FConfirmationDialogAction& Action : Descriptor->ButtonActions)
		{
			TObjectPtr<UInputAction> InputAction;

			switch(Action.Result)
			{
			case ECommonMessagingResult::Confirmed:
				InputAction = ConfirmedInputAction;
				break;
			case ECommonMessagingResult::Declined:
				InputAction = DeclinedInputAction;
				break;
			case ECommonMessagingResult::Cancelled:
				InputAction = CancelledInputAction;
				break;
			default:
				ensure(false);
				continue;
			}

			UExtendedCommonButtonBase* Button = EntryBox_Buttons->CreateEntry<UExtendedCommonButtonBase>();
			if (IsValid(Button))
			{
				Button->SetTriggeringEnhancedInputAction(InputAction);
				Button->SetButtonText(Action.OptionalDisplayText);
				Button->OnClicked().AddUObject(this, &ThisClass::CloseConfirmationWindow, Action.Result);
			}
		}
	}
	
	OnResultCallback = ResultCallback;
}

void UExtendedCommonDialog::KillDialog()
{
	Super::KillDialog();
}

void UExtendedCommonDialog::CloseConfirmationWindow(ECommonMessagingResult Result)
{
	DeactivateWidget();
	OnResultCallback.ExecuteIfBound(Result);
}
