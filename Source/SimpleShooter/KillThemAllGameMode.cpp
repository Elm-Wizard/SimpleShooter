// Fill out your copyright notice in the Description page of Project Settings.


#include "KillThemAllGameMode.h"


void AKillThemAllGameMode::PawnKilled(APawn *PawnKilled) 
{
    Super::PawnKilled(PawnKilled);

    APlayerController *PlayerController = Cast<APlayerController>(PawnKilled->GetController());

    // Ako je igrac mrtav -> kraj igre
    if (PlayerController != nullptr)
    {
        PlayerController->GameHasEnded(nullptr, false); // false znaci da nije kontroler igraca koji je pobedio
    }
    
}
