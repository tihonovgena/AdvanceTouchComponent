// Copyright 2024 Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AdvanceTouchComponent.h"
#include "TapComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTapSignature, FVector2D, TouchLocation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDoubleTapSignature, FVector2D, TouchLocation);

UCLASS(Blueprintable, ClassGroup=(TouchControl), meta=(BlueprintSpawnableComponent, DisplayName="TapComponent"))
class ADVANCETOUCHCONTROLLERS_API UTapComponent : public UAdvanceTouchComponent
{
	GENERATED_BODY()

public:
	UTapComponent();

	UPROPERTY(BlueprintAssignable)
	FOnTapSignature OnTap;

	UPROPERTY(BlueprintAssignable)
	FOnDoubleTapSignature OnDoubleTap;
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnHandleTap(FVector2D TapLocation);

	UFUNCTION()
	virtual void OnHandleDoubleTap(FVector2D TapLocation);

private:
	// Range time that within will detect tap
	UPROPERTY(EditDefaultsOnly, Category = "Controller|Tap")
	float DetectionTapTime;

	// Range time that within will detect double tap
	UPROPERTY(EditDefaultsOnly, Category = "Controller|Tap")
	float DetectionDoubleTapTime;

};
