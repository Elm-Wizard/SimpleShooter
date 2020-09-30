// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController.h"
#include "ShooterCharacter.h"
#include "BTTask_Shoot.h"


UBTTask_Shoot::UBTTask_Shoot() 
{
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) 
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if (OwnerComp.GetAIOwner() == nullptr)
    {
        return EBTNodeResult::Failed;
    }
    
    AShooterCharacter *Character = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn()); // Dohvata karaktera kastovanjem radi dolazenja do funkcije za pucanje
    if (Character == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    Character->Shoot(); // Poziva funkciju za pucanje

    return EBTNodeResult::Succeeded;
}
