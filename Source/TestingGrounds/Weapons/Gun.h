// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class AMannequin;

UCLASS()
class TESTINGGROUNDS_API AGun : public AActor
{
	GENERATED_BODY()
	
		/** Gun mesh: 1st person view (seen only by self) */
		//UPROPERTY(BlueprintReadOnly, Category = Mesh)


	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USceneComponent* FP_MuzzleLocation;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* Mesh1P;

public:	
	// Sets default values for this actor's properties
	AGun();

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector GunOffset;
	UFUNCTION(BlueprintCallable)
	void OnFire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* FP_Gun;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AMannequin* Parent;



	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ABallProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimInstance* AnimInstance;
};
