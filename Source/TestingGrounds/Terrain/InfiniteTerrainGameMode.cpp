

// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorPool.h"
#include "GameFramework/Volume.h"
#include "EngineUtils.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "InfiniteTerrainGameMode.h"

AInfiniteTerrainGameMode::AInfiniteTerrainGameMode()
{
	NavMeshPool = CreateDefaultSubobject<UActorPool>(FName("NavMeshPool"));

}


void AInfiniteTerrainGameMode::AddToPool(AVolume* VolumeToAdd)
{
	UE_LOG(LogTemp, Warning, TEXT("VOLUME = %s"), *VolumeToAdd->GetName())
	if (VolumeToAdd->ActorHasTag(FName("NAVMESH")))
	{ 
		NavMeshPool->Add(VolumeToAdd);
		UE_LOG(LogTemp, Warning, TEXT("VOLUME = %s"), *VolumeToAdd->GetName()) 
	}
}

void AInfiniteTerrainGameMode::StartPlay()
{
	Super::StartPlay();
	PopulateBoundVolumePool();
}

void AInfiniteTerrainGameMode::PopulateBoundVolumePool()
{
	if (!ensure(GetWorld())) {return;}
	auto VolumeIterator = TActorIterator<AVolume>(GetWorld());
		while (VolumeIterator)
		{
			AddToPool(*VolumeIterator);
			++VolumeIterator;
		}
}