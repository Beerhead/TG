// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Tile.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//HISMC = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("Grass"));

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	HISMC = FindComponentByClass<UHierarchicalInstancedStaticMeshComponent>();

}

void CreateGrass() 
{
	for (int i = 0; i < NumToSpawn; i++)
		HISMC->AddInstance()
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::PlaceActors(TSubclassOf<AActor> ActorToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	int NumToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	//UE_LOG(LogTemp, Warning, TEXT("ACTOR LOC = %s"), *GetActorLocation().ToString())
	for (int i = 0; i < NumToSpawn; i++)
	{	
		FVector SpawnPlace;
		float Scale = FMath::RandRange(MinScale, MaxScale);
		if (GetEmptyPlace(SpawnPlace, Radius*Scale))
		{	
			float Rotation = FMath::RandRange(-180.f, 180.f);
			PlaceActor(ActorToSpawn, SpawnPlace, Rotation, Scale);
		}
	}
}


bool ATile::GetEmptyPlace(FVector &OutLocation, float Radius)
{	
	const int32 Tries = 25;
	int32 Try = 0;
	while (Try < Tries)
	{
		Try++;
		OutLocation = FMath::RandPointInBox(FBox(FVector(78, -1800, -120), FVector(3891, 1767, -120)));
		if (IsCanSpawnInLocation(OutLocation, Radius))
		{
			return true;
		}
	}
	return false;
}

void ATile::PlaceActor(TSubclassOf<AActor> ActorToSpawn, FVector PlaceToSpawn, float Rotation, float Scale)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ActorToSpawn);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Spawned->SetActorRelativeLocation(PlaceToSpawn);
	Spawned->SetActorRotation(FRotator(0, Rotation, 0));
	Spawned->SetActorScale3D(FVector(Scale));
	
}

bool ATile::IsCanSpawnInLocation(FVector Location, float Radius)
{
	FHitResult HitResult;
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		GlobalLocation,
		GlobalLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(Radius));
	auto Color = HasHit ? FColor(255, 0, 0) : FColor(0, 255, 0);
	//DrawDebugSphere(GetWorld(),GlobalLocation,Radius,16,Color,true);
	
		return !HasHit;
}

void CreateGrass()
{
}
