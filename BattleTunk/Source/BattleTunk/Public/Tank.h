// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Item.h"
#include "Tank.generated.h" // Must be last include.

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
/* @brief
* Responsible for taking damage.
*/
UCLASS()
class BATTLETUNK_API ATank : public APawn
{
	GENERATED_BODY()
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this pawn's properties
	ATank();
	// Called by the engine when actor damage is dealt.
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// Return current health as a percentage of base health, between 0 and 1.
	UFUNCTION(Blueprintpure, Category = Health)
	float GetHealthPercent() const;

	UFUNCTION(BlueprintImplementableEvent, Category = Camera)
		void ShakeCamera();

	void GetItem(EItemKind ItemKind, float EffectsTime, float Effects);


protected:
	void DestroyTank();
	void OnQuitGame();

public:
	FOnDeath TankDeathDelegate;
	UPROPERTY(BlueprintReadOnly, Category = State)
		bool bIsPlayerTank = false;

protected:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float DestroyDelay = 0.3f;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		int32 Health = 100;
	UPROPERTY(VisibleAnywhere, Category = Health)
		int32 CurrentHealth = 0;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		bool bIsMovableTank = true;

	bool bTankDied = false;

	UParticleSystemComponent* ExplosionBlast = nullptr;
	
	class ABattleTunkGameMode* GameModeRef = nullptr;
	class UTankAimingComponent* TankAiming = nullptr;
	class UTankMovementComponent* TankMovement = nullptr;

};
