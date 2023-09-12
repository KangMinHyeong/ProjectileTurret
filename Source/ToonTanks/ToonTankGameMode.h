// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTankGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTankGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	void ActorDied(AActor* DestroyedActor);

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:
	class ATank* Tank;
	class AToonTankPlayerController* ToonTankPlayerController;

	void HandleGameStart();

	UPROPERTY(EditAnywhere)
	float StartDelay = 3;

	int32 TargetTowers = 0;
	int32 GetTargetTowersCount();

protected:
	virtual void BeginPlay() override;

};
