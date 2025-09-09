// Copyright (C) 2024 Van de Walle Bastien
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0


#include "ExtendedCommonUserWidget.h"

int32 UExtendedCommonUserWidget::GetOwningLocalPlayerIndex() const
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

bool UExtendedCommonUserWidget::IsOwningLocalPlayer(int32 PlayerIndex) const
{
	return PlayerIndex != INDEX_NONE && PlayerIndex == GetOwningLocalPlayerIndex();
}
