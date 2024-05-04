// Copyright 2024 Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Enums/BlueprintTouchPins.h"
#include "Structs/ATCTouchData.h"

#include "AdvanceTouchSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(AdvanceTouchSubsystem, Log, All);

namespace ETouchIndex
{
	enum Type : int;
}

class UAdvanceTouchComponent;

/*
 * This class to init of all touch components in the actor where we run setup
 * It distribute touch input to priority controllers and manage handling of controllers
 */

UCLASS()
class ADVANCETOUCHCONTROLLERS_API UAdvanceTouchSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

protected:	
virtual void Deinitialize() override;

public:
	// Finds Mobile Control Components and adds them to array
	void SetupTouchControllers(const AActor* OwnerComponents, UInputComponent* PlayerInputComponent);

	// Blueprint function
	UFUNCTION(BlueprintCallable, Category="AdvanceTouchControllers")
	void SetupTouchControllers(const AActor* OwnerComponents);

#pragma region TouchInputsEvents
public:
	// Distribute input params to the TouchComponent
	void HandleTouchInput(ETouchIndex::Type FingerIndex, EInputEvent Type, const FVector2D& TouchLocation);

	// Converts the function friendly to Blueprint into a C++ function
	UFUNCTION(BlueprintCallable, Category="AdvanceTouchControllers", meta=(ExpandEnumAsExecs = "InTouchPins"))
	void HandleTouchInput(const ETouchPins::Type InTouchPins, const FVector& Location, const ETouchIndex::Type FingerIndex, AActor* OwnerComponents);

	UFUNCTION()
	void OnInputTouchPressedEvent(ETouchIndex::Type FingerIndex, FVector Location);
	UFUNCTION()
	void OnInputTouchRepeatEvent(ETouchIndex::Type FingerIndex, FVector Location);
	UFUNCTION()
	void OnInputTouchReleasedEvent(ETouchIndex::Type FingerIndex, FVector Location);
#pragma endregion 
	
#pragma region TouchComponents
private:
	void SortTouchComponentsByPriority(TArray<UAdvanceTouchComponent*>& Array);
	
	// Store all touch components for current actor
	TArray<UAdvanceTouchComponent*> TouchComponents;

	TArray<UAdvanceTouchComponent*>& GetTouchComponents(){return TouchComponents;}
	
	void FindTouchControllersInLocation(const TArray<UAdvanceTouchComponent*>& TargetArray,
		TArray<UAdvanceTouchComponent*>& OutputArray, const FVector2D& Location);
	
	void GetHandlingTouchComponents(const TArray<FATCTouchData>& TargetTouchData,
		TArray<UAdvanceTouchComponent*>& OutputArray, const uint32 Handle);

	// Removes each ATCTouchData form HandlingTouchComponents array with desired Handle
	void RemoveTouchDataFromHandlingArray(int32 Handle);

	// Add ATCTouchData to HandlingTouchArray;
	void AddTouchDataInHandlingArray(const FATCTouchData& TouchData);
	
	TArray<FATCTouchData> HandlingTouchData;
#pragma endregion 
};
