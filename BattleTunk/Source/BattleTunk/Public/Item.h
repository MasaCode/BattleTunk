// Copyright MasaCode

#pragma once

#include "GameFramework/Actor.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum class EItemKind : uint8
{
	EHealing,
	ESpeed,
	EAttack
};

UCLASS()
class BATTLETUNK_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 bodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		EItemKind ItemKind = EItemKind::EHealing;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float Effects = 10.0f;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float EffectsTime = 10.0f;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float LifeTime = 120.0f;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		USoundCue* HitSound = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = Component)
		UStaticMeshComponent* Mesh = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = Component)
		UParticleSystemComponent* Particle = nullptr;
	
};
