// Copyright MasaCode

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnManager.generated.h"

UCLASS()
class BATTLETUNK_API ASpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = Spawning)
		void SpawnItem();

protected:
	FVector GetRandomSpawnablePoint();
	bool CheckPoint(const FVector& RandomPoint);

protected:
	UPROPERTY(EditAnywhere, Category = Setup)
		UBoxComponent* SpawnArea = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TArray<TSubclassOf<class AItem>> SpawnItems;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxHeight = 20000.0f;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinHeight = 0.0f;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float SpawnDelay = 10.0f;
	UPROPERTY(EditAnywhere, Category = Setup)
		FName SpawnFolderPath = "/Item";

	FVector Origin = FVector::ZeroVector;
	FVector BoxExtent = FVector::ZeroVector;
	FTimerHandle TimerHandle;
};
