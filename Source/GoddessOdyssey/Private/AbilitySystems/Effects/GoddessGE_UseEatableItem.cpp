// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/Effects/GoddessGE_UseEatableItem.h"
#include "DebugHelper.h"

UGoddessGE_UseEatableItem::UGoddessGE_UseEatableItem()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;
}

void UGoddessGE_UseEatableItem::SetEffectHealingAmount(float InHealAmount)
{
	ClearModifiers();
	
	FGameplayModifierInfo Modifier;
	Modifier.Attribute = Attribute;
	Modifier.ModifierOp = EGameplayModOp::Additive;
	Modifier.ModifierMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(InHealAmount));
	Modifiers.Add(Modifier);
}

void UGoddessGE_UseEatableItem::ClearModifiers()
{
	if (!Modifiers.IsEmpty())
		Modifiers.Empty();
}
