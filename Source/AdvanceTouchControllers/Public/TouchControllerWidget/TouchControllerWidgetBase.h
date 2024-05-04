// Copyright 2024 Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TouchControllerWidgetBase.generated.h"

class USizeBox;
class UCanvasPanel;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnControllerUpdateRequestSignature);

UCLASS(Abstract)
class ADVANCETOUCHCONTROLLERS_API UTouchControllerWidgetBase : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

#pragma region ControllerProperties
protected:
	// Use that method in a blueprint widget for init USizeBox that will include your control widgets
	UFUNCTION(BlueprintCallable, Category="AdvanceTouchControllers|Widget")
	void SetupBoxSize(USizeBox* SizeBox);
	
	UFUNCTION(BlueprintCallable, Category="AdvanceTouchControllers|Widget")
	FVector2D GetControllerSize() const {return ControllerSize;}
	
	UFUNCTION(BlueprintCallable, Category="AdvanceTouchControllers|Widget")
	FVector2D GetControllerPosition() const {return  ControllerPosition;}

private:
	UPROPERTY()
	TObjectPtr<USizeBox> ControllerSizeBox;
	
	FVector2D ControllerSize;
	FVector2D ControllerPosition;
	
public:
	void UpdateSizeBox();
	void SetControllerSize(const FVector2D& Size);
	void SetControllerPosition(const FVector2D& Position);

	UFUNCTION()
	virtual void OnUpdateControllerWidget();

	UPROPERTY(BlueprintAssignable)
	FOnControllerUpdateRequestSignature OnControllerUpdateRequest;
#pragma endregion 
	
	
#pragma region Debug
public:
	void SetEnableDebug(bool Enable) {bEnableDebug = Enable;}
	void SetDebugGeometryPoints(const TArray<FVector2D>& BorderPoints){ DebugGeometryPoints = BorderPoints;}
	
protected:
	void PaintDebugGeometry(FSlateWindowElementList& OutDrawElements,
		int32 LayerId, const TArray<FVector2D>& Points) const;

private:
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
		const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements,
		int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	// Inherits from the controller
	bool bEnableDebug = false;
	
	TArray<FVector2D> DebugGeometryPoints;
#pragma endregion
};
