// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTunk.h"
#include "Tank.h"
#include "BattleTunkGameMode.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"


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

	CurrentHealth = Health;

	// Getting Particle System
	ExplosionBlast = FindComponentByClass<UParticleSystemComponent>();
	ExplosionBlast->PrimaryComponentTick.bCanEverTick = false;

	// Getting TankAimingComponent
	TankAiming = FindComponentByClass<UTankAimingComponent>();

	// Getting TankMovementComponent
	TankMovement = FindComponentByClass<UTankMovementComponent>();

	// Getting GameMode Reference
	GameModeRef = Cast<ABattleTunkGameMode>(this->GetWorld()->GetAuthGameMode());

	if (!ExplosionBlast) {
		UE_LOG(LogTemp, Error, TEXT("Particle System not found"));
	}
	if (!TankAiming) {
		UE_LOG(LogTemp, Error, TEXT("Tnak Aiming not Found"));
	}
	if (!TankMovement && bIsMovableTank) {
		UE_LOG(LogTemp, Error, TEXT("Tank Movement not Found"));
	}
	if (!GameModeRef) {
		UE_LOG(LogTemp, Error, TEXT("Tank Game Mode not Found"));
	}

}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction(FName("Quit"), IE_Pressed, this, &ATank::OnQuitGame);
}

float ATank::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) 
{
	int32 DamagePoints = FPlatformMath::RoundToInt(Damage);
	int32 DamageToApply = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealth);
	
	CurrentHealth -= DamageToApply;

	if (bIsPlayerTank) {
		ShakeCamera();
	}

	if (CurrentHealth <= 0 && !bTankDied) {
		// Tank died.
		TankDeathDelegate.Broadcast();
		bTankDied = true;

		FTimerHandle Handle;
		this->GetWorld()->GetTimerManager().SetTimer(Handle, this, &ATank::DestroyTank, DestroyDelay, false);
	
		if (!ExplosionBlast) return DamageToApply;
		ExplosionBlast->Activate();
	}
	
	return DamageToApply;
}

float ATank::GetHealthPercent() const
{
	return ((float)CurrentHealth / (float)Health);
}

void ATank::GetItem(EItemKind ItemKind, float EffectsTime, float Effects)
{
	FString ItemType;

	switch (ItemKind) {
		case EItemKind::EHealing:
		{
			CurrentHealth = FMath::Clamp<int32>((CurrentHealth + int32(Effects)), 0, Health);
			ItemType = "Heal Item";
			return;
		}
		case EItemKind::EAttack:
		{
			if (TankAiming) {
				TankAiming->ChangeProjectile(EffectsTime, (int32)(Effects));
			}
			ItemType = "Attack Item";
			return;
		}
		case EItemKind::ESpeed:
		{
			if (TankMovement) {
				TankMovement->SetItemEffects(EffectsTime, Effects);
			}
			ItemType = "Speed up Item";
			return;
		}
	}

}


void ATank::DestroyTank()
{
	Cast<ABattleTunkGameMode>(this->GetWorld()->GetAuthGameMode())->ChangeTankLeft();
	Destroy();
}

void ATank::OnQuitGame()
{
	UKismetSystemLibrary::QuitGame(this, this->GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit);
}