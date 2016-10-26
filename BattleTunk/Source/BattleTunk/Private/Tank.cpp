// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTunk.h"
#include "Tank.h"
#include "BattleTunkGameMode.h"

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

	ExplosionBlast = FindComponentByClass<UParticleSystemComponent>();
	ExplosionBlast->PrimaryComponentTick.bCanEverTick = false;
	if (!ExplosionBlast) {
		UE_LOG(LogTemp, Error, TEXT("Particle System not found"));
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



void ATank::DestroyTank()
{
	Cast<ABattleTunkGameMode>(this->GetWorld()->GetAuthGameMode())->ChangeTankLeft();
	Destroy();
}

void ATank::OnQuitGame()
{
	UKismetSystemLibrary::QuitGame(this, this->GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit);
}