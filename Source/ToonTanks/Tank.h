// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	APlayerController* GetTankPlayerController() const {return PlayerControllerRef;}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category="Components")
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category="Components")
	class USpringArmComponent* SpringArm;

	void Move(float Value);

	void Turn(float Value);

	UPROPERTY(EditAnywhere)
	float Speed = 200;

	UPROPERTY(EditAnywhere)
	float TurnRate = 200;

	APlayerController* PlayerControllerRef;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	bool bLive = true;
};
