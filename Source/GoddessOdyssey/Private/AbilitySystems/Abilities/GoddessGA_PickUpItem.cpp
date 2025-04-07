// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/Abilities/GoddessGA_PickUpItem.h"

#include "DebugHelper.h"
#include "Characters/Goddess.h"
#include "Components/SphereComponent.h"
#include "Components/Inventory/GoddessInventoryComponent.h"
#include "Item/PickUps/InventoryItemBase.h"
#include "Kismet/KismetSystemLibrary.h"

void UGoddessGA_PickUpItem::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo,
                                            const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGoddessGA_PickUpItem::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                       const FGameplayAbilityActorInfo* ActorInfo,
                                       const FGameplayAbilityActivationInfo ActivationInfo,
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
		{
			// 防止装备着的武器被拾取
			if (FoundItem->GetPickUpCollisionSphere()->GetGenerateOverlapEvents())
				CollectedItems.AddUnique(FoundItem);
		}
	}

	if (CollectedItems.IsEmpty())
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
}

void UGoddessGA_PickUpItem::AddToItemInvnetory()
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
			FGoddessInventoryItemData NewInventoryItemData =
				GetGoddessInventoryComponentFromActorInfo()->GetSavedInventoryItemData();
			UDataTable* AllInventoryItemsDataTable =
				GetGoddessInventoryComponentFromActorInfo()->GetAllInventoryItemsDataTable();
			if (AllInventoryItemsDataTable)
			{
				InventoryItem->AddToInventory(AllInventoryItemsDataTable, NewInventoryItemData);
				GetGoddessInventoryComponentFromActorInfo()->SetSavedInventoryItemData(NewInventoryItemData);
				// GetGoddessInventoryComponentFromActorInfo()->PrintSavedInventoryItemData();
			}
			else
				Debug::Print(TEXT("AllInventoryItemsDataTable is nullptr"));
		}
	}
}
