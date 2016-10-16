// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "GameFramework/PlayerController.h"
#include "PlayerTankController.generated.h" // Must be the last include.

class UTankAimingComponent;
/**
 * Responsible for helping the player aim.
 */
UCLASS()
class BATTLETUNK_API APlayerTankController : public APlayerController
{
	GENERATED_BODY()
	
public: // For public member functions.
	UFUNCTION()
	void OnTankDeath();

	void AimTowardsCrosshair();
	
protected:
	virtual void SetPawn(APawn* InPawn) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
		void FoundAimingComponent(UTankAimingComponent* AimCompRef);

	UFUNCTION(BlueprintImplementableEvent, Category = Death)
		void PlayerDeath();

private: // For private member functions.
	bool GetSightRayHitLocation(FVector& OUT_HitLocation) const;
	bool GetLookDirection(const FVector2D& ScreenLocation, FVector& OUT_LookDirection) const;
	bool GetLookVectorHitLocation(const FVector& LookDirection, FVector& OUT_HitLocation) const;

public: // For public member variables.

	UPROPERTY(EditDefaultsOnly)
		float CrossHairLocationX = 0.5f;
	UPROPERTY(EditDefaultsOnly)
		float CrossHairLocationY = 0.3333;
	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000.0f; // 10km.

protected: // For private member variables.
	UPROPERTY(BlueprintReadOnly, Category = State)
		UTankAimingComponent* mTankAimingComponent = nullptr;
	
private:
	bool bGameEnd = false;

};
