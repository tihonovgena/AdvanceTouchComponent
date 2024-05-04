// Copyright 2024 Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "AdvanceTouchComponent.generated.h"

namespace EControllerAlignment
{
	enum Type : uint8;
}

namespace ETouchType
{
	enum Type : int;
}

class UTouchHandleBase;
class UTouchControllerWidgetBase;
class UTouchBorderBase;

DECLARE_LOG_CATEGORY_EXTERN(AdvanceTouchComponent, Log, All);

UCLASS(Abstract, ClassGroup=(TouchControl))
class ADVANCETOUCHCONTROLLERS_API UAdvanceTouchComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAdvanceTouchComponent();
	virtual void FinishDestroy() override;
	
protected:
	virtual void BeginPlay() override;

public:	
	void InputTouch(ETouchIndex::Type FingerIndex, const EInputEvent Type, const FVector2D& TouchLocation, FDateTime DeviceTimestamp);

	// True if our touch in the border
	bool IsTouchedController(const FVector2D& TouchLocation) const;
	
#pragma region ControllerBorder
protected:
	UTouchBorderBase* GetControllerBorder() const {return ControllerBorder;}
	
	UPROPERTY()
	TSubclassOf<UTouchBorderBase> ControllerBorderClass;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Controller")
	TSubclassOf<UTouchControllerWidgetBase> BorderWidgetClass;
	
	UTouchBorderBase* CreateControllerBorder();

	UPROPERTY()
	TObjectPtr<UTouchBorderBase> ControllerBorder;
#pragma endregion 

#pragma region ControllerHandle
protected:
	UTouchHandleBase* GetControllerHandle() const {return ControllerHandle;}
	
	UPROPERTY()
	TSubclassOf<UTouchHandleBase> ControllerHandleClass;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Controller")
	TSubclassOf<UTouchControllerWidgetBase> HandleWidgetClass;
	
	UTouchHandleBase* CreateControllerHandle();
	
	UPROPERTY()
	TObjectPtr<UTouchHandleBase> ControllerHandle;
#pragma endregion 
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="AdvanceTouchControllers|TouchComponent")
	int32 GetPriority() const {return Priority;}

protected:
	UPROPERTY(EditDefaultsOnly, Category="Controller")
	TEnumAsByte<EControllerAlignment::Type> Alignment;

	// Raw offset, it will consider DPI scale
	UPROPERTY(EditDefaultsOnly, Category="Controller")
	FVector2D Offset;
	
private:	
	// "0 - low priority, 1 and more - higher priority"
	UPROPERTY(EditDefaultsOnly, Category="Controller")
	int32 Priority;
	
	// If enable it shows debug of the border and the control on the screen
	UPROPERTY(EditDefaultsOnly, Category="Controller")
	bool bShowDebug;

		
};
