// Copyright 2024 Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AdvanceTouchComponent/Modules/TouchControllerBase.h"

#include "TouchBorderBase.generated.h"

class UControllerBorderWidget;

UCLASS(Abstract, Blueprintable)
class ADVANCETOUCHCONTROLLERS_API UTouchBorderBase : public UTouchControllerBase
{
	GENERATED_BODY()

public:
	virtual bool IsTouchInputInBorder(const FVector2D& TouchLocation);
	
};
