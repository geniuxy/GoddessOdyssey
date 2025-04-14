// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/Abilities/GoddessGA_EnterShop.h"

#include "DebugHelper.h"
#include "Characters/Goddess.h"
#include "Characters/NPC.h"
#include "Item/PickUps/InventoryItemBase.h"
#include "Kismet/KismetSystemLibrary.h"

void UGoddessGA_EnterShop::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo,
                                           const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGoddessGA_EnterShop::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                      const FGameplayAbilityActorInfo* ActorInfo,
                                      const FGameplayAbilityActivationInfo ActivationInfo,
                                      bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGoddessGA_EnterShop::LookForNearestNPC()
{
	NearestNPC = nullptr;

	TArray<FHitResult> TraceHits;

	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetGoddessFromActorInfo(),
		GetGoddessFromActorInfo()->GetActorLocation(),
		GetGoddessFromActorInfo()->GetActorLocation() + -GetGoddessFromActorInfo()->GetActorUpVector() * TraceDistance,
		TraceBoxSize / 2.f,
		(-GetGoddessFromActorInfo()->GetActorUpVector()).ToOrientationRotator(),
		NPCTraceChannel,
		false,
		TArray<AActor*>(),
		bDrawDebugBox ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		TraceHits,
		true
	);

	float NearestDistance = TNumericLimits<float>::Max();
	for (const FHitResult& Hit : TraceHits)
	{
		if (ANPC* FoundNPC = Cast<ANPC>(Hit.GetActor()))
		{
			float Distance = FVector::Distance(GetGoddessFromActorInfo()->GetActorLocation(),
			                                   Hit.GetActor()->GetActorLocation());
			if (Distance < NearestDistance)
			{
				NearestDistance = Distance;
				NearestNPC = FoundNPC;
			}
		}
	}

	if (NearestNPC == nullptr)
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
}

void UGoddessGA_EnterShop::OpenShopOverlay()
{
	if (NearestNPC == nullptr)
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
		return;
	}
	GetGoddessFromActorInfo()->SetTalkingNPC(NearestNPC);
	NearestNPC->EnterShoppingMode(GetGoddessFromActorInfo());
}
