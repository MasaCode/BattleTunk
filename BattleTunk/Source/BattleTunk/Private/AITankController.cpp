// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTunk.h"
#include "AITankController.h"

#include "Tank.h"

void AAITankController::BeginPlay()
{
	Super::BeginPlay();
	
	mTank = Cast<ATank>(GetPawn());
	mPlayerTank = Cast<ATank>(this->GetWorld()->GetFirstPlayerController()->GetPawn());
	
	if (!mPlayerTank) {
		UE_LOG(LogTemp, Error, TEXT("Player Tank not found"));
	}
	if (!mTank) {
		UE_LOG(LogTemp, Error, TEXT("AI Tank not found"));
	}
	
}

void AAITankController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	
	if (!mTank || !mPlayerTank) return;

	{ // Fire if the tank is aiming at player.
		mTank->AimAt(mPlayerTank->GetActorLocation());
		mTank->Fire();
	}
}
