// Copyright 2024 Tikhonov Gennadii, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "ButtonComponent.h"
#include "RectButtonComponent.generated.h"


UCLASS(Blueprintable, ClassGroup=(TouchControl), meta=(BlueprintSpawnableComponent, DisplayName="RectButtonComponent"))
class ADVANCETOUCHCONTROLLERS_API URectButtonComponent : public UButtonComponent
{
	GENERATED_BODY()

public:
	URectButtonComponent();

protected:
	virtual void BeginPlay() override;

private:	
	// Raw size, it will consider DPI scale
	UPROPERTY(EditDefaultsOnly, Category="Controller|Button")
	FVector2D ButtonSize;

};
