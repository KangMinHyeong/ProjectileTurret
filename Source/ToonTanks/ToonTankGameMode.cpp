// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameMode.h"
#include "Tank.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTankPlayerController.h"
#include "Engine/TimerHandle.h"

void AToonTankGameMode::ActorDied(AActor *DestroyedActor)
{
    if(Tank == DestroyedActor)
    {
        Tank->HandleDestruction();
        if(ToonTankPlayerController)
        {
            ToonTankPlayerController->PlayerEnableState(false);
        }
        GameOver(false);
    }
    else if(ATower* Tower = Cast<ATower>(DestroyedActor))
    {
        Tower->HandleDestruction();
        --TargetTowers;
        if(TargetTowers == 0)
        {
            GameOver(true);
        }
    }
}

void AToonTankGameMode::HandleGameStart()
{
    TargetTowers = GetTargetTowersCount();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    ToonTankPlayerController = Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    GameStart();
    if(ToonTankPlayerController)
    {
        ToonTankPlayerController->PlayerEnableState(false);
        
        FTimerHandle PlayerEnableTimerHandle;
        
        FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(
            ToonTankPlayerController,
            &AToonTankPlayerController::PlayerEnableState,
            true
        );
        GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, TimerDelegate, StartDelay, false);
    }
}

int32 AToonTankGameMode::GetTargetTowersCount()
{
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
    return Towers.Num();
}

void AToonTankGameMode::BeginPlay()
{
    Super::BeginPlay();

    HandleGameStart();
}


