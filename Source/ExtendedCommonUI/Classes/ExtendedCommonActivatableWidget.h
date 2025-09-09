// Copyright (C) 2024 Van de Walle Bastien
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0

#pragma once

#include "CommonActivatableWidget.h"
#include "ExtendedCommonActionTypes.h"
#include "CommonInputModeTypes.h"

#include "ExtendedCommonActivatableWidget.generated.h"

UENUM(BlueprintType)
enum class EExtendedCommonInputMode : uint8
{
	Menu			UMETA(Tooltip = "Input is received by the UI only"),
	Game			UMETA(Tooltip = "Input is received by the Game only"),
	GameAndMenu		UMETA(Tooltip = "Input is received by UI and the Game"),
	Default			UMETA(Tooltip = "Use the default input mode"),

	MAX 			UMETA(Hidden)
};

/**
 * Extends UCommonActivatableWidget with Blueprint-visible functions for registering additional input action bindings.
 */
UCLASS(meta = (DisableNativeTick))
class EXTENDEDCOMMONUI_API UExtendedCommonActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

	// UUserWidget implementation Begin
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	// UUserWidget implementation End

	// UCommonActivatableWidget implementation Begin
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;
	// UCommonActivatableWidget implementation End

	UFUNCTION(BlueprintCallable, Category = ExtendedActivatableWidget)
	void RegisterInputActionBinding(FDataTableRowHandle InputAction, const FInputActionExecutedDelegate& Callback, FInputActionBindingHandle& BindingHandle, 
		bool bInDisplayInActionBar = true, ECommonInputMode InputMode = ECommonInputMode::Menu);

	UFUNCTION(BlueprintCallable, Category = ExtendedActivatableWidget)
	void UnregisterInputActionBinding(FInputActionBindingHandle& BindingHandle);

	UFUNCTION(BlueprintCallable, Category = ExtendedActivatableWidget)
	void UnregisterAllInputActionBindings();

protected:
	UFUNCTION(BlueprintPure)
	int32 GetOwningLocalPlayerIndex() const;
	
	UFUNCTION(BlueprintPure)
	bool IsOwningLocalPlayer(int32 PlayerIndex) const;
	
	UPROPERTY(EditAnywhere, Category=Activation)
	bool bSetFocusToGameViewportOnDeactivated = false;

	UPROPERTY(EditAnywhere, Category=Cursor)
	bool bIsAnalogMovementEnabled = false;

	UPROPERTY(EditAnywhere, Category=Input)
	EExtendedCommonInputMode InputConfig = EExtendedCommonInputMode::Default;

	UPROPERTY(EditAnywhere, Category=Input)
	EMouseCaptureMode GameMouseCaptureMode = EMouseCaptureMode::NoCapture;

private:
	UPROPERTY(Transient)
	TArray<FUIActionBindingHandle> BindingHandles;

	TSharedPtr<class FExtendedCommonAnalogCursor> AnalogCursor;
};
