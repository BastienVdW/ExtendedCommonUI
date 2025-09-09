// Copyright (C) 2024 Van de Walle Bastien
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0


#include "ExtendedCommonUIActionRouter.h"

#include "ExtendedCommonAnalogCursor.h"

TSharedRef<FCommonAnalogCursor> UExtendedCommonUIActionRouter::MakeAnalogCursor() const
{
	return FCommonAnalogCursor::CreateAnalogCursor<FExtendedCommonAnalogCursor>(*this);
}
