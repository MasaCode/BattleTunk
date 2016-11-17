// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "BattleTunkGameMode.generated.h"


/**
 * 
 */
UCLASS()
class BATTLETUNK_API ABattleTunkGameMode : public AGameMode
{
	GENERATED_BODY()
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
	void ChangeTankLeft();

	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
		void SetTankLeft();

public:
	UPROPERTY(BlueprintReadWrite, Category = State)
		int32 TankLeft = 0;


};
