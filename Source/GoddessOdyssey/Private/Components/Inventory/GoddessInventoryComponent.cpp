// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Inventory/GoddessInventoryComponent.h"

#include "DebugHelper.h"
#include "GoddessFunctionLibrary.h"
#include "AbilitySystems/BaseAbilitySystemComponent.h"
#include "AbilitySystems/Effects/GoddessGE_CustomEffect.h"
#include "Characters/Goddess.h"

void UGoddessInventoryComponent::PrintSavedInventoryItemData()
{
	for (FGoddessSlotData Weapon : SavedInventoryItemData.Weapons)
	{
		Debug::Print(FString::Printf(TEXT("Weapon ID: %s, Quantity: %d"), *Weapon.ItemID.RowName.ToString(),
		                             Weapon.Quantity));
	}

	for (FGoddessSlotData Shield : SavedInventoryItemData.Shields)
	{
		Debug::Print(FString::Printf(TEXT("Shield ID: %s, Quantity: %d"), *Shield.ItemID.RowName.ToString(),
		                             Shield.Quantity));
	}

	for (FGoddessSlotData Eatable : SavedInventoryItemData.Eatables)
	{
		Debug::Print(FString::Printf(TEXT("Eatable ID: %s, Quantity: %d"), *Eatable.ItemID.RowName.ToString(),
		                             Eatable.Quantity));
	}
}

void UGoddessInventoryComponent::UseEatableInventoryItem(float HealAmount)
{
	check(EatableGameplayEffectClass);

	UGoddessGE_CustomEffect* HealEffect = EatableGameplayEffectClass->GetDefaultObject<UGoddessGE_CustomEffect>();

	// 设置动态回血量
	HealEffect->SetEffectAmount(HealAmount);
	
	// 应用GameplayEffect到角色
	UBaseAbilitySystemComponent* AbilitySystemComponent =
		UGoddessFunctionLibrary::NativeGetASCFromActor(Cast<AGoddess>(GetOwningPawn()));
	if (AbilitySystemComponent)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		AbilitySystemComponent->ApplyGameplayEffectToSelf(HealEffect, 1.0f, EffectContext);
	}

	HealEffect->ClearModifiers();
}
