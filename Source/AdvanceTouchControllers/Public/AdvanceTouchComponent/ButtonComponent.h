// Copyright 2024 Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AdvanceTouchComponent.h"
#include "ButtonComponent.generated.h"

/*
 * Abstract class of buttons, use RectButtonComponent or CircleButtonComponent instead
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPressedSignature, FVector2D, TouchLocation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProcessingSignature, FVector2D, TouchLocation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReleasedSignature, FVector2D, TouchLocation);

UCLASS(Abstract, ClassGroup=(TouchControl))
class ADVANCETOUCHCONTROLLERS_API UButtonComponent : public UAdvanceTouchComponent
{
	GENERATED_BODY()

public:
	UButtonComponent();

	UPROPERTY(BlueprintAssignable)
	FOnPressedSignature OnPressed;

	UPROPERTY(BlueprintAssignable)
	FOnProcessingSignature OnProcessing;

	UPROPERTY(BlueprintAssignable)
	FOnReleasedSignature OnReleased;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void OnHandleTouchBegun(FVector2D TouchLocation);
	
	UFUNCTION()
	void OnHandleTouchEnded(FVector2D TouchLocation);

	UFUNCTION()
	void OnHandleTouchMoved(FVector2D TouchLocation);

private:
	void SetLastTouchPosition(const FVector2D& TouchLocation){LastTouchPosition = TouchLocation;}
	FVector2D LastTouchPosition;
	bool IsPressed;
};
