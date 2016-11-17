// Copyright MasaCode

#include "BattleTunk.h"
#include "SpawnManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Item.h"


// Sets default values
ASpawnManager::ASpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(FName( "Spawn Area" ));
	SetRootComponent(SpawnArea);

}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();
	
	Origin = SpawnArea->Bounds.Origin;
	BoxExtent = SpawnArea->Bounds.BoxExtent;

	SpawnItem();
	this->GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASpawnManager::SpawnItem, SpawnDelay, true);
}

void ASpawnManager::SpawnItem()
{
	FVector SpawnLocation = GetRandomSpawnablePoint();
	int ItemIndex = UKismetMathLibrary::RandomIntegerInRange(0, SpawnItems.Num() - 1);
	auto Item = this->GetWorld()->SpawnActor<AItem>(SpawnItems[ItemIndex], SpawnLocation, FRotator::ZeroRotator);
	//Item->SetFolderPath(SpawnFolderPath);
}

FVector ASpawnManager::GetRandomSpawnablePoint()
{
	bool bCanSpawn = false;
	FVector Point;

	while (!bCanSpawn) {
		Point = UKismetMathLibrary::RandomPointInBoundingBox(Origin, BoxExtent);
		bCanSpawn = CheckPoint(Point);
	}

	return Point;
}

bool ASpawnManager::CheckPoint(const FVector& RandomPoint)
{
	FHitResult Hit;
	FVector StartLocation = RandomPoint;
	FVector EndLocation = RandomPoint;

	StartLocation.Z = MaxHeight;
	EndLocation.Z = -10000.0f;
	
	this->GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility);

	if ((Hit.Location.Z <= RandomPoint.Z) && (Hit.Location.Z >= MinHeight)) {\
		return true;
	}
	return false;
}
