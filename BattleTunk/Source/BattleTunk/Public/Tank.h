// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Must be last include.

class UTankAimingComponent;

class UTankBarrel;
class UTankTurret;

class AProjectile;

UCLASS()
class BATTLETUNK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	
	void AimAt(const FVector& HitLocation);

	UFUNCTION(BlueprintCallable, Category = Action)
	void Fire();

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


protected:
	//UPROPERTY(BlueprintReadOnly)
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 4000.0f; 
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeInSecond = 3.0f;
	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint; // alternative http://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/TsubclassOf/

	// Local barrel pointer to spawn projectile based-on barrel's location.
	UTankBarrel* mBarrel = nullptr;
	
	float mLastFiringTime = 0.0;

};
