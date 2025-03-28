// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/Abilities/GoddessGA_PickUpStone.h"

#include "Characters/Goddess.h"
#include "Item/PickUps/StoneBase.h"
#include "Kismet/KismetSystemLibrary.h"

void UGoddessGA_PickUpStone::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGoddessGA_PickUpStone::EndAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility,
	bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGoddessGA_PickUpStone::CollectStones()
{
	CollectedStones.Empty();

	TArray<FHitResult> TraceHits;

	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetGoddessFromActorInfo(),
		GetGoddessFromActorInfo()->GetActorLocation(),
		GetGoddessFromActorInfo()->GetActorLocation() + -GetGoddessFromActorInfo()->GetActorUpVector() * TraceDistance,
		TraceBoxSize / 2.f,
		(-GetGoddessFromActorInfo()->GetActorUpVector()).ToOrientationRotator(),
		StoneTraceChannel,
		false,
		TArray<AActor*>(),
		bDrawDebugBox ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		TraceHits,
		true
	);

	for (const FHitResult& Hit : TraceHits)
	{
		if (AStoneBase* FoundStone = Cast<AStoneBase>(Hit.GetActor()))
			CollectedStones.AddUnique(FoundStone);
	}

	if (CollectedStones.IsEmpty())
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
}

void UGoddessGA_PickUpStone::ConsumeStones()
{
	if (CollectedStones.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
		return;
	}

	for (AStoneBase* Stone : CollectedStones)
	{
		if (Stone)
			Stone->Consume(GetBaseAbilitySystemComponentFromActorInfo(), GetAbilityLevel());
	}
}
