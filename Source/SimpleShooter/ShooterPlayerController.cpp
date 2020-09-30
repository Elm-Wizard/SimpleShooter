// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerManager.h"
#include "ShooterPlayerController.h"


void AShooterPlayerController::GameHasEnded(class AActor *EndGameFocus, bool bIsWinner) 
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    // Restartuje nivo na tajmeru
    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}
