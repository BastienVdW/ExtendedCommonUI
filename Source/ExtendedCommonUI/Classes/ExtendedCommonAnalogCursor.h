// Copyright (C) 2024 Van de Walle Bastien
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0

#pragma once

#include "CoreMinimal.h"
#include "Input/CommonAnalogCursor.h"

class EXTENDEDCOMMONUI_API FExtendedCommonAnalogCursor : public FCommonAnalogCursor
{
public:
	FExtendedCommonAnalogCursor(const UCommonUIActionRouterBase& InActionRouter) : FCommonAnalogCursor(InActionRouter) {}

public:
	bool ShouldVirtualAcceptSimulateMouseButton(const FKeyEvent& InKeyEvent, EInputEvent InputEvent) const override;
	void SetIsAnalogMovementEnabled(bool bEnable);
	void SetNormalizedCursorPosition(const FVector2D& InNormalizedCursorPosition);
	
};
