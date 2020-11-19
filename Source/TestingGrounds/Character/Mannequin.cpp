// Fill out your copyright notice in the Description page of Project Settings.

#include "../Weapons/Gun.h"
#include "Mannequin.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ChildActorComponent.h"


// Sets default values
AMannequin::AMannequin()
{
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;


	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	ArmsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterArmsMesh"));
	ArmsMesh->SetOnlyOwnerSee(true);
	ArmsMesh->SetupAttachment(FirstPersonCameraComponent);
	ArmsMesh->bCastDynamicShadow = false;
	ArmsMesh->CastShadow = false;
	ArmsMesh->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	ArmsMesh->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	//Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
	//Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	//Gun->bCastDynamicShadow = false;
	//Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	//FP_Gun->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();
	if (GunToAttach == NULL) { return; }
	UE_LOG(LogTemp, Warning, TEXT("USE NORM!"))
		Gun = GetWorld()->SpawnActor<AGun>(GunToAttach);
	Gun->AnimInstance = ArmsMesh->GetAnimInstance();
	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	Gun->AttachToComponent(ArmsMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
}

// Called every frame
void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UE_LOG(LogTemp, Warning, TEXT("input stup!!!!!"))
	//Super::SetupPlayerInputComponent(PlayerInputComponent);
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMannequin::PullTrigger);



	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AMannequin::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMannequin::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMannequin::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMannequin::LookUpAtRate);
}

void AMannequin::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AMannequin::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AMannequin::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMannequin::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMannequin::PullTrigger()
{
	bIsFiring = true;
	bIsAiming = true;
	Gun->OnFire();
}


