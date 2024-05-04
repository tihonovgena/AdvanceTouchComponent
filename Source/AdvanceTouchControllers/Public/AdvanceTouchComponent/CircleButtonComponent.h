// Copyright 2024 Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "ButtonComponent.h"
#include "CircleButtonComponent.generated.h"


UCLASS(Blueprintable, ClassGroup=(TouchControl), meta=(BlueprintSpawnableComponent, DisplayName="CircleButtonComponent"))
class ADVANCETOUCHCONTROLLERS_API UCircleButtonComponent : public UButtonComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCircleButtonComponent();

protected:
	virtual void BeginPlay() override;

private:	
	// Raw size, it will consider DPI scale
	UPROPERTY(EditDefaultsOnly, Category="Controller|Button")
	float ButtonRadius;

};
