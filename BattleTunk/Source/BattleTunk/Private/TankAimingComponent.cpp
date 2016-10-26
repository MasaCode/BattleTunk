// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTunk.h"
#include "TankAimingComponent.h"

#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = false;
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) 
{
	mBarrels.Add(BarrelToSet);
	mTurret = TurretToSet;
}

void UTankAimingComponent::InitializeWithMultipleBarrel(TArray<UTankBarrel*> BarrelsToSet, UTankTurret* TurretToSet)
{
	mBarrels.Append(BarrelsToSet);
	mTurret = TurretToSet;
}



void UTankAimingComponent::AimAt(const FVector& HitLocation) 
{
	if (!ensure(mTurret)) return;
	if (mBarrels.Num() == 0) return;

	FVector LaunchVelocity;
	FVector StartLocation = mBarrels[mBarrelIndex]->GetSocketLocation(FName("Projectile"));

	// Calculate the OutLaunchVelocity.
	if (UGameplayStatics::SuggestProjectileVelocity(this, LaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace)) {
		AimDirection = LaunchVelocity.GetSafeNormal();
		FRotator DeltaRotator;
		GetDeltaRotator(DeltaRotator);
		MoveTurretTowards(DeltaRotator.Yaw);
		MoveBarrelTowards(DeltaRotator.Pitch);
		
	}
}

bool UTankAimingComponent::Fire()
{
	if (mBarrels.Num() == 0) return false;
	if (!ensure(ProjectileBlueprint)) return false;

	auto projectile = this->GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, mBarrels[mBarrelIndex]->GetSocketLocation(FName("Projectile")), mBarrels[mBarrelIndex]->GetSocketRotation(FName("Projectile")));
	projectile->LaunchProjectile(LaunchSpeed);
	
	mBarrelIndex = (mBarrelIndex + 1) % mBarrels.Num();

	return true;
}


void UTankAimingComponent::MoveTurretTowards(float Yaw) 
{
	if (FMath::Abs(Yaw) > 180)
		Yaw = -Yaw;

	mTurret->Rotate(Yaw);
}

void UTankAimingComponent::MoveBarrelTowards(float Pitch)
{
	mBarrels[mBarrelIndex]->Elevate(Pitch);
}

void UTankAimingComponent::GetDeltaRotator(FRotator& OUT_DeltaRotator) 
{
	FRotator BarrelRotator = mBarrels[mBarrelIndex]->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	OUT_DeltaRotator = AimAsRotator - BarrelRotator;
}

bool UTankAimingComponent::IsBarrelMoving() 
{
	if (mBarrels[0] == nullptr) return false;
	return (!AimDirection.Equals(mBarrels[mBarrelIndex]->GetForwardVector(), 0.01));
}