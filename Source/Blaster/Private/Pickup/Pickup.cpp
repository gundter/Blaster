// Copyright Serico Games


#include "Pickup/Pickup.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	
	OverlapSphere = CreateDefaultSubobject<USphereComponent>("Overlap Sphere");
	OverlapSphere->SetupAttachment(GetRootComponent());
	OverlapSphere->SetSphereRadius(150.f);
	OverlapSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("Pickup Mesh");
	PickupMesh->SetupAttachment(OverlapSphere);
	PickupMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APickup::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		OverlapSphere->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnSphereOverlap);
	}
}

void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bSweep, const FHitResult& SweepResult)
{
	
}

void APickup::Destroyed()
{
	Super::Destroyed();

	if (PickupSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
	}
}

