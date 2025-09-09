// Copyright (C) 2024 Van de Walle Bastien
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0

#pragma once

#include "CoreMinimal.h"

#include "ExtendedCommonListWidgetTypes.generated.h"

USTRUCT(BlueprintType)
struct EXTENDEDCOMMONUI_API FExtendedCommonListWidgetItem
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText LocalizedName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText LocalizedDescription;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> IconTexture;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bLocked = false;
};
