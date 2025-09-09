// Copyright (C) 2024 Van de Walle Bastien
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0


#include "ExtendedPrimaryGameLayout.h"

#include "ExtendedPrimaryGameLayoutTypes.h"
#include "Subsystems/ExtendedCommonMessagingSubsystem.h"

void UExtendedPrimaryGameLayout::NativeConstruct()
{
	Super::NativeConstruct();

	RegisterLayer(TAG_UI_LAYER_MODAL,		Modal_Stack);
	RegisterLayer(TAG_UI_LAYER_MENU,			Menu_Stack);
	RegisterLayer(TAG_UI_LAYER_GAMEMENU,		GameMenu_Stack);
	RegisterLayer(TAG_UI_LAYER_GAMELAYER,	GameLayer_Stack);
}
