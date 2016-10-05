// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTunk.h"
#include "AITankController.h"

#include "Tank.h"

void AAITankController::BeginPlay()
{
	Super::BeginPlay();
	
	mTank = GetControlledTank();
	FindPlayerControlledTank();
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

	mTank->AimAt(mPlayerTank->GetActorLocation());

}

ATank* AAITankController::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());
}

void AAITankController::FindPlayerControlledTank() 
{
	mPlayerTank = Cast<ATank>(this->GetWorld()->GetFirstPlayerController()->GetPawn());
}