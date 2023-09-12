// Fill out your copyright notice in the Description page of Project Settings.


#include "Health.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTankGameMode.h"

// Sets default values for this component's properties
UHealth::UHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealth::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHP;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealth::TakeDamage);
	
	ToonTankGameMode = Cast<AToonTankGameMode>(UGameplayStatics::GetGameMode(this));
}


// Called every frame
void UHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealth::TakeDamage(AActor *DamageActor, float Damage, const UDamageType *DamageType, AController *Instigator, AActor *DamageCauser)
{
	if(Damage <= 0.0f)
	{
		return;
	}

	Health = Health - Damage;

	if(Health <= 0.0f && ToonTankGameMode)
	{
		ToonTankGameMode->ActorDied(DamageActor);
	}
}
