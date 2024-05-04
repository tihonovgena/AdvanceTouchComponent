// Copyright 2024 Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AdvanceTouchComponent.h"
#include "StickComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStickSignature, float, AxisX, float, AxisY);

/*
 * Abstract class for stick component, it has only stick functionality without visual
 */

UCLASS(Abstract, ClassGroup=(TouchControl), meta=(BlueprintSpawnableComponent, DisplayName="StickComponent"))
class ADVANCETOUCHCONTROLLERS_API UStickComponent : public UAdvanceTouchComponent
{
	GENERATED_BODY()

public:
	UStickComponent();

	UPROPERTY(BlueprintAssignable)
	FOnStickSignature OnStick;

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Controller|Stick")
	float HandleRadius;
	
	// If true, stick will have always same base position 
	UPROPERTY(EditDefaultsOnly, Category="Controller|Stick")
	bool bLockedStick;
	
	// Raw handle length it will apply DPI scale
	UPROPERTY(EditDefaultsOnly, Category="Controller|Stick")
	float HandleLength;

	UPROPERTY(EditDefaultsOnly, Category="Controller|Stick")
	FVector2D StickBackgroundSize;

	bool bProcessing;
	float LastAxisX;
	float LastAxisY;

	UFUNCTION()
	void OnControllerBorderUpdateVisual();
	
	UFUNCTION()
	void OnHandleTouchBegun(const FVector2D& Location, float AxisX, float AxisY);

	UFUNCTION()
	void OnHandleTouchMoved(const FVector2D& Location, float AxisX, float AxisY);

	UFUNCTION()
	void OnHandleTouchEnded(const FVector2D& Location, float AxisX, float AxisY);
	
};
