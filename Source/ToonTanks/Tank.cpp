// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"


ATank::ATank()
{
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));

    SpringArm->SetupAttachment(RootComponent);
    Camera->SetupAttachment(SpringArm);

}

void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);

}

void ATank::BeginPlay()
{
    Super::BeginPlay();

    PlayerControllerRef = Cast<APlayerController>(GetController());

}

void ATank::Move(float Value)
{
    FVector Location = FVector(0, 0, 0);

    Location.X = Value * Speed *  UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalOffset(Location, true);
}

void ATank::Turn(float Value)
{
    FRotator Rotation = FRotator::ZeroRotator;

    Rotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(Rotation, true);
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(PlayerControllerRef)
    {   
        FHitResult HitResult;
        PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
               
        ABasePawn::TurretRotation(HitResult.ImpactPoint);
    }
}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();

    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    bLive = false;
}
