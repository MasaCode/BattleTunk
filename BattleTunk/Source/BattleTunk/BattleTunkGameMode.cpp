// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTunk.h"
#include "BattleTunkGameMode.h"
#include "Tank.h"

void ABattleTunkGameMode::BeginPlay()
{
	Super::BeginPlay();
	SetTankLeft();
}
