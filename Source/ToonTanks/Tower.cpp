// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


void ATower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(TimeRateHandle, this, &ATower::CheckFireCondition, TimeRate, true);
}

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(CheckRange())
    {
        ABasePawn::TurretRotation(Tank->GetActorLocation());
    }

}

bool ATower::CheckRange()
{
    if(Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        if(Distance < Range)
        {
            return true;
        }
    }
    return false;
}

void ATower::HandleDestruction()
{
    Super::HandleDestruction();

    Destroy();
}

void ATower::CheckFireCondition()
{
    if(Tank == nullptr)
    {
        return;
    }
    if(CheckRange() && Tank->bLive)
    {
        Fire();
    }
    
}
