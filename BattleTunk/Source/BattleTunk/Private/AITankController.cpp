// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTunk.h"
#include "AITankController.h"



void AAITankController::BeginPlay()
{
	Super::BeginPlay();
	
	//mPlayerTank = GetPlayerControlledTank();
	FindPlayerControlledTank();
	if (!mPlayerTank) {
		UE_LOG(LogTemp, Error, TEXT("Player Tank not found"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Foud Player Tank %s"), *(mPlayerTank->GetName()));
	}
	

}

ATank* AAITankController::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());
}

ATank* AAITankController::GetPlayerControlledTank() const 
{
	return Cast<ATank>(this->GetWorld()->GetFirstPlayerController()->GetPawn());
}

void AAITankController::FindPlayerControlledTank() 
{
	mPlayerTank = Cast<ATank>(this->GetWorld()->GetFirstPlayerController()->GetPawn());
}