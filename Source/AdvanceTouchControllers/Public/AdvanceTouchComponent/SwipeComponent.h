// Copyright 2024 Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AdvanceTouchComponent.h"
#include "SwipeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSwipeUpSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSwipeDownSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSwipeLeftSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSwipeRightSignature);

UCLASS(Blueprintable, ClassGroup=(TouchControl), meta=(BlueprintSpawnableComponent, DisplayName = "SwipeComponent"))
class ADVANCETOUCHCONTROLLERS_API USwipeComponent : public UAdvanceTouchComponent
{
	GENERATED_BODY()

public:
	USwipeComponent();

	UPROPERTY(BlueprintAssignable)
	FOnSwipeUpSignature OnSwipeUp;

	UPROPERTY(BlueprintAssignable)
	FOnSwipeDownSignature OnSwipeDown;

	UPROPERTY(BlueprintAssignable)
	FOnSwipeLeftSignature OnSwipeLeft;

	UPROPERTY(BlueprintAssignable)
	FOnSwipeRightSignature OnSwipeRight;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Controller|Swipe")
	float DetectionSwipeTime;

private:
	UFUNCTION()
	void OnHandleSwipeUp();
	
	UFUNCTION()
	void OnHandleSwipeDown();

	UFUNCTION()
	void OnHandleSwipeLeft();

	UFUNCTION()
	void OnHandleSwipeRight();
	
};
