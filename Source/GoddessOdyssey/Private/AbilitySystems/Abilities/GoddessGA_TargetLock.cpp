// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/Abilities/GoddessGA_TargetLock.h"

#include "DebugHelper.h"
#include "Animation/AnimInstanceProxy.h"
#include "Characters/Goddess.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void UGoddessGA_TargetLock::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	TryLockOnTarget();

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGoddessGA_TargetLock::EndAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility,
	bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGoddessGA_TargetLock::TryLockOnTarget()
{
	GetAvailableActorsToLock();
}

void UGoddessGA_TargetLock::GetAvailableActorsToLock()
{
	AGoddess* Goddess = GetGoddessFromActorInfo();

	TArray<FHitResult> BoxTraceHits;

	UKismetSystemLibrary::BoxTraceMultiForObjects(
		Goddess,
		Goddess->GetActorLocation(),
		Goddess->GetActorLocation() + Goddess->GetActorForwardVector() * BoxTraceDistance,
		TraceBoxSize / 2.f,
		Goddess->GetActorForwardVector().ToOrientationRotator(),
		BoxTraceChannels,
		false,
		TArray<AActor*>(),
		bShowPersistentDebugShape ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
		BoxTraceHits,
		true
	);

	for (const FHitResult& TraceHit : BoxTraceHits)
	{
		if (AActor* HitActor = TraceHit.GetActor())
		{
			if (HitActor != Goddess)
			{
				AvailableActorsToLock.AddUnique(HitActor);

				Debug::Print(HitActor->GetActorNameOrLabel());
			}
		}
	}
}
