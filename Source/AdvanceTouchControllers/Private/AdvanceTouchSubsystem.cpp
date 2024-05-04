// Copyright 2024 Tikhonov Gennadii, All Rights Reserved


#include "AdvanceTouchSubsystem.h"
#include "Structs/ATCTouchData.h"

#include "AdvanceTouchComponent/AdvanceTouchComponent.h"

DEFINE_LOG_CATEGORY(AdvanceTouchSubsystem)

void UAdvanceTouchSubsystem::Deinitialize()
{
	UE_LOG(AdvanceTouchSubsystem, Log, TEXT("AdvanceTouchSubsystem runs deinitialize"))
	Super::Deinitialize();
}

void UAdvanceTouchSubsystem::SetupTouchControllers(const AActor* OwnerComponents, UInputComponent* PlayerInputComponent)
{
	
	// Clears last controls array for being sure we will not use previous controls
	TouchComponents.Empty();

	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindTouch(IE_Pressed, this, &UAdvanceTouchSubsystem::OnInputTouchPressedEvent);
		PlayerInputComponent->BindTouch(IE_Repeat, this, &UAdvanceTouchSubsystem::OnInputTouchRepeatEvent);
		PlayerInputComponent->BindTouch(IE_Released, this, &UAdvanceTouchSubsystem::OnInputTouchReleasedEvent);
	}
	
	for (const auto Element : OwnerComponents->GetComponents())
	{
		UAdvanceTouchComponent* MobileControlComponent = Cast<UAdvanceTouchComponent>(Element);
		if (IsValid(MobileControlComponent))
		{
			TouchComponents.Add(MobileControlComponent);
		}
	}
	
	SortTouchComponentsByPriority(TouchComponents);
	
}

void UAdvanceTouchSubsystem::SetupTouchControllers(const AActor* OwnerComponents)
{
	SetupTouchControllers(OwnerComponents, nullptr);
}


void UAdvanceTouchSubsystem::HandleTouchInput(ETouchIndex::Type FingerIndex, EInputEvent Type, const FVector2D& TouchLocation)
{
	TArray<UAdvanceTouchComponent*> HandlingTouchComponents;
	GetHandlingTouchComponents(HandlingTouchData, HandlingTouchComponents, FingerIndex);
	
	// Checks if input just began
	if (Type == IE_Pressed)
	{
		// Bug with touch stuck beyond screen, it happens only in editor
		for (const auto TouchComponent : HandlingTouchComponents)
		{
			RemoveTouchDataFromHandlingArray(FingerIndex);
		}
		
		// Searches for which control to assign a touch by location
		TArray<UAdvanceTouchComponent*> AssignedControllers;
		FindTouchControllersInLocation(TouchComponents, AssignedControllers, TouchLocation);
		
		if (!AssignedControllers.IsEmpty())
		{
			for (const auto AssignedController : AssignedControllers)
			{
				if (AssignedController)
				{
					AssignedController->InputTouch(FingerIndex, Type, TouchLocation, FDateTime::Now());
					// Adds the control to handling array to be and only that control would use the handle
					const TWeakObjectPtr<UAdvanceTouchComponent> ControllerWeakPtr = AssignedController;

					FATCTouchData TouchData;
					TouchData.Handle = FingerIndex;
					TouchData.TouchComponent = ControllerWeakPtr;
					AddTouchDataInHandlingArray(TouchData);
				}
			}
		}
		
	}
	// Otherwise checks if it is handling
	else
	{
		for (const auto TouchComponent : HandlingTouchComponents)
		{
			TouchComponent->InputTouch(FingerIndex, Type, TouchLocation, FDateTime::Now());
		}

		// Removes the control from handling array to say in can be handle by another control
		if (Type == IE_Released)
		{
			RemoveTouchDataFromHandlingArray(FingerIndex);
		}
	}
}

void UAdvanceTouchSubsystem::HandleTouchInput(const ETouchPins::Type InTouchPins, const FVector& Location, const ETouchIndex::Type FingerIndex, AActor* OwnerComponents)
{
	//Converts a ETouchPins enum into EInputEvent enum
	EInputEvent TouchType;
	switch (InTouchPins)
	{
		case ETouchPins::Pressed:
			TouchType = IE_Pressed;
			break;
		case ETouchPins::Moved:
			TouchType = IE_Axis;
			break;
		case ETouchPins::Released:
			TouchType = IE_Released;
			break;
		default:
			return;
	}
	
	HandleTouchInput(FingerIndex, TouchType, FVector2D(Location.X, Location.Y));
}

void UAdvanceTouchSubsystem::SortTouchComponentsByPriority(TArray<UAdvanceTouchComponent*>& Array)
{
	Array.Sort([] (const UAdvanceTouchComponent& ControllerA, const UAdvanceTouchComponent& ControllerB)
		{
			return ControllerA.GetPriority() > ControllerB.GetPriority();
		}
	);
}

void UAdvanceTouchSubsystem::FindTouchControllersInLocation(const TArray<UAdvanceTouchComponent*>& TargetArray,
		TArray<UAdvanceTouchComponent*>& OutputArray, const FVector2D& Location)
{
	int32 CurrentPriority = 0;
	
	for (const auto TouchComponent : TargetArray)
	{
		UAdvanceTouchComponent* Element = TouchComponent;
		if (Element && Element->IsTouchedController(Location) && Element->GetPriority() >= CurrentPriority)
			{
				// Set the first found element priority to search only in that priority group
				// We want detect several touch controllers only in one priority group
				CurrentPriority = Element->GetPriority();
				OutputArray.Add(Element);
			}
	}
}

void UAdvanceTouchSubsystem::GetHandlingTouchComponents(const TArray<FATCTouchData>& TargetTouchData,
		TArray<UAdvanceTouchComponent*>& OutputArray, const uint32 Handle)
{
	for (auto TouchData : TargetTouchData)
	{
		UAdvanceTouchComponent* TouchComponent = TouchData.TouchComponent.Get();
		if (TouchData.Handle == Handle && TouchComponent)
		{
			OutputArray.Add(TouchComponent);
		}
	}
}

void UAdvanceTouchSubsystem::RemoveTouchDataFromHandlingArray(int32 Handle)
{
	HandlingTouchData.RemoveAll([Handle](const FATCTouchData& TouchData)
	{
		return TouchData.Handle == Handle;
	});
}

void UAdvanceTouchSubsystem::AddTouchDataInHandlingArray(const FATCTouchData& TouchData)
{
	HandlingTouchData.Add(TouchData);
}

void UAdvanceTouchSubsystem::OnInputTouchPressedEvent(ETouchIndex::Type FingerIndex, FVector Location)
{
	const FVector2D Vector2D(Location.X, Location.Y);
	HandleTouchInput(FingerIndex, IE_Pressed, Vector2D);
}

void UAdvanceTouchSubsystem::OnInputTouchRepeatEvent(ETouchIndex::Type FingerIndex, FVector Location)
{
	const FVector2D Vector2D(Location.X, Location.Y);
	HandleTouchInput(FingerIndex, IE_Repeat, Vector2D);
}

void UAdvanceTouchSubsystem::OnInputTouchReleasedEvent(ETouchIndex::Type FingerIndex, FVector Location)
{
	const FVector2D Vector2D(Location.X, Location.Y);
	HandleTouchInput(FingerIndex, IE_Released, Vector2D);
}
