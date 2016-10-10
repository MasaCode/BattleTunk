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
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}



void ATank::AimAt(const FVector& HitLocation)
{
	if (!ensure(TankAimingComponent)) return;

	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire() 
{
	auto currentTime = this->GetWorld()->GetTimeSeconds();

	if (((currentTime - mLastFiringTime) < ReloadTimeInSecond)) return;
	if (!ensure(mBarrel)) return;

	auto projectile = this->GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, mBarrel->GetSocketLocation(FName("Projectile")), mBarrel->GetSocketRotation(FName("Projectile")));
	projectile->LaunchProjectile(LaunchSpeed);
	mLastFiringTime = currentTime;

}
