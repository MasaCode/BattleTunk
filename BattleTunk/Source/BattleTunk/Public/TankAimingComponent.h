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
	FS_Reloading UMETA(DisplayName = "Reloading"),
	FS_OutOfAmo UMETA(DisplayName = "OutOfAmo")
};


/*
** Holds barrel's properties and Elevates method.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETUNK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	// For public member function.

	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = Setup)
		void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
		void InitializeWithMultipleBarrel(TArray<UTankBarrel*> BarrelsToSet, UTankTurret* TurretToSet);
	
	void AimAt(const FVector& HitLocation);

	UFUNCTION(BlueprintCallable, Category = Action)
	bool Fire();

	void ChangeProjectile(float EffectsTime, int32 NewProjectileIndex);
	void DisableItemEffects();

	bool IsBarrelMoving();

private: // For private memeber function.

	void GetDeltaRotator(FRotator& OUT_DeltaRotator);
	void MoveBarrelTowards(float Pitch);
	void MoveTurretTowards(float Yaw);

protected: // For protected member variable.

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 4000.0f;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TArray<TSubclassOf<AProjectile>> ProjectileBlueprints;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		FName SpawnFolderPath = "/Projectile";

	/*UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;*/

private: // For private member variables.
	TArray<UTankBarrel*> mBarrels;
	UTankTurret* mTurret = nullptr;
	class ATank* mTank = nullptr;
	FTimerHandle TimerHandle;

	FVector AimDirection = FVector(0.0f);
	int32 mBarrelIndex = 0;
	int32 mProjectileIndex = 0;
};
