// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "particles/ParticleSystem.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);


	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> Fire(TEXT("/Game/AssetPacks/ParagonWraith/FX/Particles/Abilities/Primary/FX/P_Wraith_Primary_MuzzleFlash.P_Wraith_Primary_MuzzleFlash"));
	if(Fire.Succeeded()){
		MuzzleFlash = Fire.Object;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> Hit(TEXT("/Game/AssetPacks/ShooterGame/Effects/ParticleSystems/Weapons/AssaultRifle/Impacts/P_AssaultRifle_IH.P_AssaultRifle_IH"));
	if(Hit.Succeeded()){
		ImpactEffect = Hit.Object;
	}

}

void AGun::PullTrigger()
{
	GameStatic->SpawnEmitterAttached(MuzzleFlash, Mesh, FName("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn == nullptr) return;
	AController* OwnerController = OwnerPawn->GetController();
	if(OwnerController == nullptr) return;
	
	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	
	FVector End = Location + Rotation.Vector() * MaxRange;
	
	FHitResult HitResult;

	if(GetWorld()->LineTraceSingleByChannel(HitResult, Location, End, ECollisionChannel::ECC_GameTraceChannel1)){
		FVector ShootDirection = -Rotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, HitResult.Location, ShootDirection.Rotation());
	}
	
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

