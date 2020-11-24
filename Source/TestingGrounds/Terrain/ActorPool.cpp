// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorPool.h"

// Sets default values for this component's properties
UActorPool::UActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}

AActor* UActorPool::CheckOut()
{
	if (Pool.Num() == 0) { return nullptr; }
	return Pool.Pop();
}

void UActorPool::Return(AActor* ActorToReturn)
{	
	if (!ensure(ActorToReturn)) 
	{ 
				UE_LOG(LogTemp, Warning, TEXT("NO ACTOR TO RETURN"))
			return;
	}
	UE_LOG(LogTemp, Warning, TEXT("ACTOR %s RETURNED"), *ActorToReturn->GetName())
		Pool.Push(ActorToReturn);
}

void UActorPool::Add(AActor* ActorToAdd)
{
	if (!ensure(ActorToAdd))
	{
		UE_LOG(LogTemp, Warning, TEXT("NO ACTOR TO ADD"))
		return;
	}
	Pool.Push(ActorToAdd);
	UE_LOG(LogTemp, Warning, TEXT("ACTOR %s ADDED"), *ActorToAdd->GetName())
}
