// Fill out your copyright notice in the Description page of Project Settings.

//#include "GameFramework/Pawn.h"
#include "Gun.h"
#include "../Character/Mannequin.h"
#include "Kismet/GameplayStatics.h"
#include "../Weapons/BallProjectile.h"


// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	//FP_Gun->SetOnlyOwnerSee(false);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	//FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));
	FP_MuzzleLocation->SetRelativeRotation(FRotator(0.f, 0.0f, 0.0f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	Parent = Cast<AMannequin>(GetParentActor());
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!Parent) { return; }
	if (Parent->bIsFiring) { OnFire(); }
}


void AGun::OnFire()
{	
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			const FRotator SpawnRotation = FP_MuzzleLocation->GetComponentRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = FP_MuzzleLocation->GetComponentLocation();

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

			// spawn the projectile at the muzzle
			World->SpawnActor<ABallProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
	
	
	if (!(AnimInstance)) { return; }
	if (!(FireAnimationFP)) { return; }
	if (!(FireAnimationTP)) { return; }
	if (!(GetAttachParentActor())) { return; }

	if (Cast<AMannequin>(GetAttachParentActor())->IsPlayerControlled())
	{
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimationFP, 1.f);
		}
	}
	else 
	{
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimationTP, 1.f);
		}
	}
}
	// try and play a firing animation if specified
