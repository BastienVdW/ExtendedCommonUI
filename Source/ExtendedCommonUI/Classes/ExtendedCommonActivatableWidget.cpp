// Copyright (C) 2024 Van de Walle Bastien
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0


#include "ExtendedCommonActivatableWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "CommonUI/Private/Input/UIActionRouterTypes.h"
#include "Engine/LocalPlayer.h"
#include "ExtendedCommonAnalogCursor.h"
#include "GameFramework/PlayerController.h"
#include "Input/CommonUIActionRouterBase.h"
#include "Input/CommonUIInputTypes.h"

void UExtendedCommonActivatableWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UExtendedCommonActivatableWidget::NativeDestruct()
{
	UnregisterAllInputActionBindings();

	Super::NativeDestruct();
}

void UExtendedCommonActivatableWidget::NativeOnActivated()
{
	Super::NativeOnActivated();

	for (const FUIActionBindingHandle& Handle : BindingHandles)
	{
		AddActionBinding(Handle);
	}

	if (bIsAnalogMovementEnabled)
	{
		if (ULocalPlayer* LocalPlayer = GetOwningLocalPlayer())
		{
			if (UCommonUIActionRouterBase* ActionRouter = LocalPlayer->GetSubsystem<UCommonUIActionRouterBase>())
			{
				AnalogCursor = StaticCastSharedPtr<FExtendedCommonAnalogCursor>(ActionRouter->GetCommonAnalogCursor());
				if (AnalogCursor.IsValid())
				{
					AnalogCursor->SetIsAnalogMovementEnabled(true);
					AnalogCursor->SetNormalizedCursorPosition(FVector2D(.5f, .5f));
				}
			}
		}
	}
}

void UExtendedCommonActivatableWidget::NativeOnDeactivated()
{
	for (const FUIActionBindingHandle& Handle : BindingHandles)
	{
		RemoveActionBinding(Handle);
	}

	if (bIsAnalogMovementEnabled && AnalogCursor.IsValid())
	{
		AnalogCursor->SetIsAnalogMovementEnabled(false);
		AnalogCursor.Reset();
	}

	Super::NativeOnDeactivated();

	if (bSetFocusToGameViewportOnDeactivated)
	{
		UWidgetBlueprintLibrary::SetFocusToGameViewport();
	}
}

int32 UExtendedCommonActivatableWidget::GetOwningLocalPlayerIndex() const
{
	const ULocalPlayer* LocalPlayer = GetOwningLocalPlayer();
	if (IsValid(LocalPlayer))
	{
		return LocalPlayer->GetLocalPlayerIndex();
	}
	else
	{
		return INDEX_NONE;
	}
}

bool UExtendedCommonActivatableWidget::IsOwningLocalPlayer(int32 PlayerIndex) const
{
	return PlayerIndex != INDEX_NONE && PlayerIndex == GetOwningLocalPlayerIndex();
}

void UExtendedCommonActivatableWidget::RegisterInputActionBinding(FDataTableRowHandle InputAction, const FInputActionExecutedDelegate& Callback, FInputActionBindingHandle& BindingHandle, 
	bool bInDisplayInActionBar /*= true*/, ECommonInputMode InputMode /*= ECommonInputMode::Menu*/)
{
	UnregisterInputActionBinding(BindingHandle);

	FBindUIActionArgs BindArgs(InputAction, FSimpleDelegate::CreateLambda([InputAction, Callback]()
		{
			Callback.ExecuteIfBound(InputAction.RowName);
		})
	);
	BindArgs.bDisplayInActionBar = bInDisplayInActionBar;
	BindArgs.InputMode = InputMode;

	BindingHandle.Handle = RegisterUIActionBinding(BindArgs);
	BindingHandles.Add(BindingHandle.Handle);
}

void UExtendedCommonActivatableWidget::UnregisterInputActionBinding(FInputActionBindingHandle& BindingHandle)
{
	if (BindingHandle.Handle.IsValid())
	{
		BindingHandles.Remove(BindingHandle.Handle);
		BindingHandle.Handle.Unregister();
	}
}

void UExtendedCommonActivatableWidget::UnregisterAllInputActionBindings()
{
	for (FUIActionBindingHandle& Handle : BindingHandles)
	{
		if (Handle.IsValid())
		{
			Handle.Unregister();
		}
	}
	BindingHandles.Empty();
}

TOptional<FUIInputConfig> UExtendedCommonActivatableWidget::GetDesiredInputConfig() const
{
	switch (InputConfig)
	{
	case EExtendedCommonInputMode::GameAndMenu:
		return FUIInputConfig(ECommonInputMode::All, GameMouseCaptureMode);
	case EExtendedCommonInputMode::Game:
		return FUIInputConfig(ECommonInputMode::Game, GameMouseCaptureMode);
	case EExtendedCommonInputMode::Menu:
		return FUIInputConfig(ECommonInputMode::Menu, EMouseCaptureMode::NoCapture);
	case EExtendedCommonInputMode::Default:
	default:
		return Super::GetDesiredInputConfig();
	}
}
