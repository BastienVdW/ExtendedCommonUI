// Copyright (C) 2024 Van de Walle Bastien
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0


#include "ExtendedCommonDescriptionOverlayWidget.h"

#include "CommonRichTextBlock.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/PanelWidget.h"

UExtendedCommonDescriptionOverlayWidget::UExtendedCommonDescriptionOverlayWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UExtendedCommonDescriptionOverlayWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	SetVisibility(ESlateVisibility::Hidden);
}

void UExtendedCommonDescriptionOverlayWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UExtendedCommonDescriptionOverlayWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (WidgetToShowDescriptionAt.IsValid())
	{
		MoveDescriptionAtWidget(WidgetToShowDescriptionAt.Get());
	}
}

void UExtendedCommonDescriptionOverlayWidget::ShowDescriptionAtWidget(const FText& InText, UWidget* InWidget)
{
	WidgetToShowDescriptionAt = InWidget;
	if (!WidgetToShowDescriptionAt.IsValid())
	{
		return;
	}
	
	SetVisibility(ESlateVisibility::HitTestInvisible);

	if (CommonRichTextBlock_Description)
	{
		CommonRichTextBlock_Description->SetText(InText);
	}

	MoveDescriptionAtWidget(WidgetToShowDescriptionAt.Get());
}

void UExtendedCommonDescriptionOverlayWidget::MoveDescriptionAtWidget(const UWidget* InWidget)
{
	if (!InWidget)
	{
		return;
	}
	
	const FGeometry& WidgetGeometry = InWidget->GetCachedGeometry();
	const FVector2D AbsolutePosition = WidgetGeometry.GetAbsolutePosition();
	const FVector2D AbsoluteSize = WidgetGeometry.GetAbsoluteSize();
	const FVector2D AbsoluteTargetPosition = AbsolutePosition + FVector2D(AbsoluteSize.X * 0.5f, AbsoluteSize.Y);

	FVector2D PixelTargetPosition = FVector2D::ZeroVector;
	FVector2D ViewportTargetPosition = FVector2D::ZeroVector;
	USlateBlueprintLibrary::AbsoluteToViewport(this, AbsoluteTargetPosition,
		PixelTargetPosition, ViewportTargetPosition);

	MoveDescriptionAtLocation(ViewportTargetPosition);
}

void UExtendedCommonDescriptionOverlayWidget::MoveDescriptionAtLocation(const FVector2D& ViewportPosition)
{
	if (PanelWidget_Description)
	{
		UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(PanelWidget_Description->Slot);
		if (ensureAlwaysMsgf(CanvasPanelSlot,
			TEXT("%hs PanelWidget_Description must be the child of a Canvas"), __FUNCTION__))
		{
			CanvasPanelSlot->SetPosition(ViewportPosition);
		}
	}
}

void UExtendedCommonDescriptionOverlayWidget::ShowDescriptionAtLocation(const FText& InText, const FVector2D& ViewportPosition)
{
	SetVisibility(ESlateVisibility::HitTestInvisible);

	if (CommonRichTextBlock_Description)
	{
		CommonRichTextBlock_Description->SetText(InText);
	}

	MoveDescriptionAtLocation(ViewportPosition);
}

void UExtendedCommonDescriptionOverlayWidget::HideDescription()
{
	SetVisibility(ESlateVisibility::Hidden);
	
	WidgetToShowDescriptionAt.Reset();	
}

