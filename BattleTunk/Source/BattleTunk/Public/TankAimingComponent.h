// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;

// Holds barrel's properties and Elevates method.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETUNK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	
	//TODO : Add SetTurretReference Function.

	

	void AimAt(const FVector& AimLocation, float LaunchSpeed);
	
private:
	void MoveBarrelTowards(const FVector& AimDirection);

private:
	UTankBarrel* mBarrel = nullptr;
	
};
