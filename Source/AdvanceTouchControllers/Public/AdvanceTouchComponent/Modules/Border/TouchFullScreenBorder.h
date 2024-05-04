// Copyright 2024 Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "TouchBorderBase.h"
#include "TouchFullScreenBorder.generated.h"


UCLASS()
class ADVANCETOUCHCONTROLLERS_API UTouchFullScreenBorder : public UTouchBorderBase
{
	GENERATED_BODY()

protected:
	virtual FVector2D GetControllerSize() const override;

public:
	virtual bool IsTouchInputInBorder(const FVector2D& TouchLocation) override;
};
