// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTunk.h"
#include "Tank.h"

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// No need to protect points as added at contructor
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet) return;

	mBarrel = BarrelToSet;
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}

void ATank::SetTurretReference(UTankTurret* TurretToSet) 
{
	if (!TurretToSet) return;

	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::AimAt(const FVector& HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire() 
{
	auto currentTime = this->GetWorld()->GetTimeSeconds();
	if (((currentTime - mLastFiringTime) < ReloadTimeInSecond) || !mBarrel) return;
		
	auto projectile = this->GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, mBarrel->GetSocketLocation(FName("Projectile")), mBarrel->GetSocketRotation(FName("Projectile")));
	projectile->LaunchProjectile(LaunchSpeed);
	mLastFiringTime = currentTime;

}
