// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaface/InteractionInterface.h"
#include "Subsystems/WorldSubsystem.h"
#include "MyTickableWorldSubsystem.generated.h"

constexpr float REFRESH_TIMER_INTERVAL = 0.25f;

/**
 * 
 */
UCLASS()
class AREASHOOTER_API UMyTickableWorldSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual void OnWorldEndPlay(UWorld& InWorld) override;
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override { return TStatId(); }
	
private:

	float RefreshTimer = REFRESH_TIMER_INTERVAL;

	UPROPERTY()
	TArray<AActor*> InteractableList;

	UPROPERTY()
	AActor* ClosestInteractable;

	UPROPERTY()
	AActor* PlayerActor;
};
