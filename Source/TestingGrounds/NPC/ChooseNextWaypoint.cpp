// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "PatrolComponent.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Super::ExecuteTask(OwnerComp, NodeMemory);
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	auto WayPoint = BlackboardComp->GetValueAsObject(WaypointKey.SelectedKeyName);
	auto Owner = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (!ensure(Owner)) { return EBTNodeResult::Failed; }
	if (!ensure(Owner->FindComponentByClass<UPatrollingComponent>())) { return EBTNodeResult::Failed; }
	auto PatrolArray = Owner->FindComponentByClass<UPatrollingComponent>()->GetPatrolPoints();

	if (PatrolArray.Num() < 1) 
	{ 
		UE_LOG(LogTemp, Warning, TEXT("No patrol points"))
			return EBTNodeResult::Failed;
	}
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolArray[Index]);
	Index++;
	auto Lenght = PatrolArray.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, (Index % Lenght));
	UE_LOG(LogTemp, Warning, TEXT("%i"), Index)

	return EBTNodeResult::Succeeded;
}
