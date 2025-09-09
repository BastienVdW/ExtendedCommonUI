// Copyright (C) 2024 Van de Walle Bastien
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0

#pragma once

#include "ExtendedCommonUserWidget.h"

#include "ExtendedCommonDescriptionOverlayWidget.generated.h"

/**
 * Widget to show a description at a location on screen.
 */
UCLASS(Abstract)
class EXTENDEDCOMMONUI_API UExtendedCommonDescriptionOverlayWidget :
	public UExtendedCommonUserWidget
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable, Category=Description)
	void ShowDescriptionAtLocation(const FText& InText, const FVector2D& ViewportPosition);

	UFUNCTION(BlueprintCallable, Category=Description)
	void ShowDescriptionAtWidget(const FText& InText, UWidget* InWidget);
	
	UFUNCTION(BlueprintCallable, Category=Description)
	void HideDescription();

	// UUserWidget implementation Begin
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	// UUserWidget implementation End
	
protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Description)
	TObjectPtr<UPanelWidget> PanelWidget_Description;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<class UCommonRichTextBlock> CommonRichTextBlock_Description;

	UPROPERTY(BlueprintReadOnly, Transient)
	TWeakObjectPtr<UWidget> WidgetToShowDescriptionAt;

	void MoveDescriptionAtWidget(const UWidget* InWidget);
	void MoveDescriptionAtLocation(const FVector2D& ViewportPosition);
};
