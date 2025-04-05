// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/Abilities/GoddessGA_PickUpItem.h"

#include "DebugHelper.h"
#include "Characters/Goddess.h"
#include "Item/PickUps/InventoryItemBase.h"
#include "Kismet/KismetSystemLibrary.h"

void UGoddessGA_PickUpItem::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGoddessGA_PickUpItem::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGoddessGA_PickUpItem::CollectItems()
{
	CollectedItems.Empty();

	TArray<FHitResult> TraceHits;

	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetGoddessFromActorInfo(),
		GetGoddessFromActorInfo()->GetActorLocation(),
		GetGoddessFromActorInfo()->GetActorLocation() + -GetGoddessFromActorInfo()->GetActorUpVector() * TraceDistance,
		TraceBoxSize / 2.f,
		(-GetGoddessFromActorInfo()->GetActorUpVector()).ToOrientationRotator(),
		ItemTraceChannel,
		false,
		TArray<AActor*>(),
		bDrawDebugBox ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		TraceHits,
		true
	);

	for (const FHitResult& Hit : TraceHits)
	{
		if (AInventoryItemBase* FoundItem = Cast<AInventoryItemBase>(Hit.GetActor()))
			CollectedItems.AddUnique(FoundItem);
	}

	if (CollectedItems.IsEmpty())
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
}

void UGoddessGA_PickUpItem::AddToInvnetory()
{
	if (CollectedItems.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
		return;
	}

	for (AInventoryItemBase* InventoryItem : CollectedItems)
	{
		if (InventoryItem)
		{
			Debug::Print(FString::Printf(TEXT("%s has been added to inventory"), *InventoryItem->GetName()));

			InventoryItem->Destroy();
		}
	}
}
