// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingComponent.h"

#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Must be last include.

UCLASS()
class BATTLETUNK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UStaticMeshComponent* BarrelToSet);

	void AimAt(const FVector& HitLocation);


private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;


protected:
	UTankAimingComponent* TankAimingComponent = nullptr;
	
	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 100000.0f; // TODO : find sensible default value.
	UPROPERTY(EditAnywhere, Category = Firing)
		float FireRate = 0.5f;

};
