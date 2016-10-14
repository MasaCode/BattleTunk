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
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay() 
{
	mLastFiringTime = this->GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) 
{
	mBarrel = BarrelToSet;
	mTurret = TurretToSet;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) 
{

	auto currentTime = this->GetWorld()->GetTimeSeconds();
	if (RoundsLeft <= 0) {
		FiringState = EFiringState::FS_OutOfAmo;
	}else if (((currentTime - mLastFiringTime) < ReloadTimeInSecond)) {
		FiringState = EFiringState::FS_Reloading;
	}
	else if (IsBarrelMoving()) {
		FiringState = EFiringState::FS_Aiming;
	}
	else {
		FiringState = EFiringState::FS_Locked;
	}

}


void UTankAimingComponent::AimAt(const FVector& HitLocation) 
{

	if (!ensure(mBarrel && mTurret)) return;

	FVector LaunchVelocity;
	FVector StartLocation = mBarrel->GetSocketLocation(FName("Projectile"));

	// Calculate the OutLaunchVelocity.
	if (UGameplayStatics::SuggestProjectileVelocity(this, LaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace)) {
		AimDirection = LaunchVelocity.GetSafeNormal();
		FRotator DeltaRotator;
		GetDeltaRotator(DeltaRotator);
		MoveTurretTowards(DeltaRotator.Yaw);
		MoveBarrelTowards(DeltaRotator.Pitch);
		
	}
}

void UTankAimingComponent::Fire()
{
	if (FiringState == EFiringState::FS_Reloading || FiringState == EFiringState::FS_OutOfAmo) return;
	if (!ensure(mBarrel && ProjectileBlueprint)) return;


	auto projectile = this->GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, mBarrel->GetSocketLocation(FName("Projectile")), mBarrel->GetSocketRotation(FName("Projectile")));
	projectile->LaunchProjectile(LaunchSpeed);
	mLastFiringTime = this->GetWorld()->GetTimeSeconds();
	RoundsLeft--;
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}

void UTankAimingComponent::MoveTurretTowards(float Yaw) 
{
	if (FMath::Abs(Yaw) > 180)
		Yaw = -Yaw;

	mTurret->Rotate(Yaw);
}

void UTankAimingComponent::MoveBarrelTowards(float Pitch)
{
	mBarrel->Elevate(Pitch); 
}

void UTankAimingComponent::GetDeltaRotator(FRotator& OUT_DeltaRotator) 
{
	FRotator BarrelRotator = mBarrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	OUT_DeltaRotator = AimAsRotator - BarrelRotator;
}

bool UTankAimingComponent::IsBarrelMoving() 
{
	if (!ensure(mBarrel)) return false;
	return (!AimDirection.Equals(mBarrel->GetForwardVector(), 0.01));
}
