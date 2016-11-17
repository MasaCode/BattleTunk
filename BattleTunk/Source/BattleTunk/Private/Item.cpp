// Copyright MasaCode

#include "BattleTunk.h"
#include "Item.h"
#include "Tank.h"


// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Creating a StaticMesh Component and Set it to RootComponent
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->bGenerateOverlapEvents = true;
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnOverlap);
	SetRootComponent(Mesh);

	// Creating a Particle.
	Particle = CreateDefaultSubobject<UParticleSystemComponent>(FName("Patricle"));
	Particle->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	this->SetLifeSpan(LifeTime);
}



void AItem::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 bodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Tank = Cast<ATank>(OtherActor);

	if (Tank) {
		UGameplayStatics::PlaySoundAtLocation(this->GetWorld(), HitSound, this->GetActorLocation(), 2.0f);
		Tank->GetItem(ItemKind, EffectsTime, Effects);
		this->Destroy();
	}

}