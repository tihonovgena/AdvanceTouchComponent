// Copyright 2024 Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Enums/ControllerAlignment.h"
#include "UObject/Object.h"

#include "TouchControllerBase.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(AdvanceTouchController, Log, All);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdateControllerVisualSignature);

class UTouchControllerWidgetBase;

/*
 * The base control module class, Controller border and Controller do Inherit that class 
 */

UCLASS(Abstract)
class ADVANCETOUCHCONTROLLERS_API UTouchControllerBase : public UObject
{
	GENERATED_BODY()
	
protected:
	UTouchControllerBase();
		
private:
	void BindResizeEvent();

protected:
	void OnViewportSizeChanged(FViewport* Viewport, uint32 Index);

	/*
	 * Start controller module block
	 */

public:
	//Necessary to run after creating, It starts processes such as bind delegates, create widgets
	virtual void RunControllerModule();

	FOnUpdateControllerVisualSignature OnUpdateControllerVisual;

protected:
	
	EControllerAlignment::Type GetAlignment() const {return ControllerAlignment;}

	FVector2D GetControllerOffset() const;

	// Raw size does not consider DPI
	virtual FVector2D GetControllerSize() const;

	// Controller size that consider DPI scale
	FVector2D GetScaledControllerSize() const;

public:
	FVector2D GetBorderPosition() const;
	void SetControllerAlignment(const EControllerAlignment::Type Type){ControllerAlignment = Type;}
	void SetControllerOffset(const FVector2D& Offset){ControllerOffset = Offset;}

	// Use for override, it is raw position without any offset
	virtual FVector2D GetControllerPosition() const;
	virtual FVector2D GetAdjustedControllerPosition() const;
	
private:
	UPROPERTY()
	TEnumAsByte<EControllerAlignment::Type> ControllerAlignment;

	// Raw offset, it will consider DPI scale
	UPROPERTY()
	FVector2D ControllerOffset;

	/*
	 * End controller module block
	 */

	/*
	* Start widget block
	* It may not use any widgets but for a debug we should have at least a base widget class
	*/
public:
	UTouchControllerWidgetBase* GetControllerWidget() const {return TouchControllerWidget;}

protected:

	void CreateControllerWidget(TSubclassOf<UUserWidget> WidgetClass);
	
	// This function should use Super after overriding to preserve basic widget updates
	// Update all your necessary properties for the widget here
	virtual void UpdateWidgetProperties();

public:	
	void SetControllerWidgetClass(const TSubclassOf<UTouchControllerWidgetBase> WidgetClass){TouchControllerWidgetClass = WidgetClass;}
	
private:
	UPROPERTY()
	TSubclassOf<UTouchControllerWidgetBase> TouchControllerWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UTouchControllerWidgetBase> TouchControllerWidget;
	/*
	 * End widget block
	 */
	

	/*
	* Start debug block
	*/	
public:
	// Should be overridden
	virtual TArray<FVector2D> GetDebugGeometryPoints();
	
	void EnableDebug(const bool Enable) { bShowDebug = Enable;}
	
protected:
	// Don't change it here it supposed to set by ControlComponent
	bool bShowDebug;
	/*
	 * End debug block
	 */
	
};
