// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;

// Holds barrel's properties and Elevates method.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETUNK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	
	void SetTurretReference(UTankTurret* TurretToSet);
	

	void AimAt(const FVector& AimLocation, float LaunchSpeed);
	
private:
	void GetDeltaRotator(const FVector& AimDirection, FRotator& OUT_DeltaRotator);
	void MoveBarrelTowards(float Pitch);
	void MoveTurretTowards(float Yaw);

private:
	UTankBarrel* mBarrel = nullptr;
	UTankTurret* mTurret = nullptr;
	
};
