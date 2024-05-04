// Copyright 2024 Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "TouchControllerWidgetBase.h"
#include "StickControllerWidget.generated.h"

UCLASS(Abstract)
class ADVANCETOUCHCONTROLLERS_API UStickControllerWidget : public UTouchControllerWidgetBase
{
	GENERATED_BODY()
	
public:
	void SetBackgroundSize(const FVector2D& Size);
	void SetBackgroundPosition(const FVector2D& Position);
	
protected:
	// Use that method in a blueprint widget for init USizeBox that will include your background widgets
	UFUNCTION(BlueprintCallable, Category="AdvanceTouchControllers|Widget")
	void SetupBackgroundBoxSize(USizeBox* SizeBox);

	virtual void OnUpdateControllerWidget() override;
	
private:
	UPROPERTY()
	TObjectPtr<USizeBox> BackgroundSizeBox;

	FVector2D BackgroundSizeBoxSize;
	FVector2D BackgroundSizeBoxPosition;

	void UpdateBackgroundSizeBox();

	
};
