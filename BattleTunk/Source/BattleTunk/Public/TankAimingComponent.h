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

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;


	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	
	void AimAt(const FVector& HitLocation);

	UFUNCTION(BlueprintCallable, Category = Action)
	void Fire();

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = Firing)
	int32 GetRoundsLeft() const;

private: // For private memeber function.

	void GetDeltaRotator(FRotator& OUT_DeltaRotator);
	void MoveBarrelTowards(float Pitch);
	void MoveTurretTowards(float Yaw);
	bool IsBarrelMoving();

protected: // For protected member variable.
	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringState FiringState = EFiringState::FS_Reloading;

private: // For private member variables.

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 4000.0f;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeInSecond = 3.0f;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		int32 RoundsLeft = 3;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UTankBarrel* mBarrel = nullptr;
	UTankTurret* mTurret = nullptr;

	float mLastFiringTime = 0.0;
	FVector AimDirection = FVector(0.0f);
};
