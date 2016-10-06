// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hideCategories = (Collision))
class BATTLETUNK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Azimuth(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSecond = 10.0f;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxAzimuth = 360.0f;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinAzimuth = 0.0f;
	
	
};
