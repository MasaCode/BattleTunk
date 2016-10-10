// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;

UENUM(BlueprintType)
enum class EFiringState : uint8
{
	FS_Locked UMETA(DisplayName = "Locked"),
	FS_Aiming UMETA(DisplayName = "Aiming"),
	FS_Reloading UMETA(DisplayName = "Reloading")
};


/*
** Holds barrel's properties and Elevates method.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETUNK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	
	void AimAt(const FVector& HitLocation);

	UFUNCTION(BlueprintCallable, Category = Action)
	void Fire();

private:
	void GetDeltaRotator(const FVector& AimDirection, FRotator& OUT_DeltaRotator);
	void MoveBarrelTowards(float Pitch);
	void MoveTurretTowards(float Yaw);

protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringState FiringState = EFiringState::FS_Aiming;

private:
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 4000.0f;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeInSecond = 3.0f;
	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UTankBarrel* mBarrel = nullptr;
	UTankTurret* mTurret = nullptr;

	float mLastFiringTime = 0.0;
};
