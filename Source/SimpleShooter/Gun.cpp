// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"

// Podesava difolt vrednosti
AGun::AGun()
{
	// Poziva se kada igra pocne ili se igrac spawnuje
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket")); // povezuje efekat sa komponentom na pusci

	// ViewPoint, implementacija LineTracea i ignorisanje aktera pri pucanju
	FHitResult Hit;
	FVector ShotDirection;
	bool bSuccess = GunTrace(Hit, ShotDirection);

	// Ako "metak pogodi"
	if (bSuccess)
	{
		// Prikaz efekta kada metak "pogodi"
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
		// Slanje i primanje stete
		AActor *HitActor = Hit.GetActor();
		if (HitActor != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			AController *OwnerController = GetOwnerController();
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
}

// Poziva se kada igra pocne ili se igrac spawnuje
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Poziva se svaki frejm
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AGun::GunTrace(FHitResult &Hit, FVector &ShotDirection)
{
	AController *OwnerController = GetOwnerController();
	if (OwnerController == nullptr)
		return false;
	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector(); // Odakle dolazi pucanj je maltene negativan rotacioni vektor

	// Implementacija LineTracea za detekciju kolizije sa "metkom"
	FVector End = Location + Rotation.Vector() * MaxRange;

	// Ignorisi pri pucanju sebe i pusku
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	// LineTrace
	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

AController *AGun::GetOwnerController() const
{
	// Dohvatanje Viewpointa igraca radi pogadjanja raycasta
	APawn *OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
		return nullptr;
	return OwnerPawn->GetController();
}
