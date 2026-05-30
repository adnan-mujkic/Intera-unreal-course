// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/MyTickableWorldSubsystem.h"
#include "EngineUtils.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void UMyTickableWorldSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	for (AActor* Actor : TActorRange<AActor>(&InWorld))
	{
		if (Actor && Actor->Implements<UInteractionInterface>())
		{
			InteractableList.Add(Actor);
		}
	}

	PlayerActor = UGameplayStatics::GetPlayerCharacter(&InWorld, 0);
}

void UMyTickableWorldSubsystem::OnWorldEndPlay(UWorld& InWorld)
{
	Super::OnWorldEndPlay(InWorld);

	InteractableList.Empty();
}

void UMyTickableWorldSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RefreshTimer -= DeltaTime;
	if (RefreshTimer > 0.f)
	{
		return;
	}

	RefreshTimer = REFRESH_TIMER_INTERVAL;

	float ClosestDistance = MAX_flt;
	for (AActor* Actor : InteractableList)
	{
		if (Actor)
		{
			const float Dist = FVector::DistSquared(Actor->GetActorLocation(), PlayerActor->GetActorLocation());
			if (Dist <= ClosestDistance)
			{
				ClosestDistance = Dist;
				ClosestInteractable = Actor;
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Updating closest interactable actor: %s, distance: %f"), ClosestInteractable ? *ClosestInteractable->GetActorNameOrLabel() : TEXT("NULL"), FMath::Sqrt(ClosestDistance));
}
