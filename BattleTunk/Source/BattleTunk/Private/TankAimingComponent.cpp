// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTunk.h"
#include "TankAimingComponent.h"

#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	mBarrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	mTurret = TurretToSet;
}

void UTankAimingComponent::AimAt(const FVector& AimLocation, float LaunchSpeed)
{
	if (!mBarrel || !mTurret) return;

	FVector LaunchVelocity;
	FVector StartLocation = mBarrel->GetSocketLocation(FName("Projectile"));

	// Calculate the OutLaunchVelocity.
	if (UGameplayStatics::SuggestProjectileVelocity(this, LaunchVelocity, StartLocation, AimLocation, LaunchSpeed, false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace)) {
		auto AimDirection = LaunchVelocity.GetSafeNormal();
		FRotator DeltaRotator;
		GetDeltaRotator(AimDirection, DeltaRotator);
		MoveTurretTowards(DeltaRotator.Yaw);
		MoveBarrelTowards(DeltaRotator.Pitch);
	}
}

void UTankAimingComponent::MoveTurretTowards(float Yaw) 
{
	mTurret->Rotate(Yaw);
}

void UTankAimingComponent::MoveBarrelTowards(float Pitch)
{
	mBarrel->Elevate(Pitch); 
}

void UTankAimingComponent::GetDeltaRotator(const FVector& AimDirection, FRotator& OUT_DeltaRotator) 
{
	FRotator BarrelRotator = mBarrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	OUT_DeltaRotator = AimAsRotator - BarrelRotator;
}