// Copyright 2024 Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "TouchBorderBase.h"
#include "TouchRectBorder.generated.h"

class URectBorderWidget;

UCLASS()
class ADVANCETOUCHCONTROLLERS_API UTouchRectBorder : public UTouchBorderBase
{
	GENERATED_BODY()

	UTouchRectBorder();

public:
	void SetRectSize(FVector2D Size){RectSize = Size;}

protected:
	virtual FVector2D GetControllerSize() const override;

private:
	virtual bool IsTouchInputInBorder(const FVector2D& TouchLocation) override;
	virtual TArray<FVector2D> GetDebugGeometryPoints() override;

	// Raw size, it will consider DPI scale
	FVector2D RectSize;
};
