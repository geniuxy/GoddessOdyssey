// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Inventory/NPCInventoryComponent.h"

#include "DebugHelper.h"
#include "GoddessFunctionLibrary.h"
#include "AbilitySystems/BaseAbilitySystemComponent.h"
#include "AbilitySystems/Effects/GoddessGE_CustomEffect.h"
#include "Characters/Goddess.h"

void UNPCInventoryComponent::PrintSavedInventoryItemData()
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

void UNPCInventoryComponent::PayMoneyForShopping(float InPrice, AActor* InCustomer)
{
	check(PayMoneyGameplayEffectClass);

	UGoddessGE_CustomEffect* MoneyEffect = PayMoneyGameplayEffectClass->GetDefaultObject<UGoddessGE_CustomEffect>();

	// 设置动态回血量
	MoneyEffect->SetEffectAmount(-InPrice);

	// 应用GameplayEffect到角色
	UBaseAbilitySystemComponent* AbilitySystemComponent =
		UGoddessFunctionLibrary::NativeGetASCFromActor(Cast<AGoddess>(InCustomer));
	if (AbilitySystemComponent)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		AbilitySystemComponent->ApplyGameplayEffectToSelf(MoneyEffect, 1.0f, EffectContext);
	}

	MoneyEffect->ClearModifiers();
}
