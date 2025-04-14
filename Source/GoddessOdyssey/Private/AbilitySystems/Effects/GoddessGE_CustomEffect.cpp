// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/Effects/GoddessGE_CustomEffect.h"

UGoddessGE_CustomEffect::UGoddessGE_CustomEffect()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;
}

void UGoddessGE_CustomEffect::SetEffectAmount(float InAmount)
{
	ClearModifiers();
	
	FGameplayModifierInfo Modifier;
	Modifier.Attribute = Attribute;
	Modifier.ModifierOp = EGameplayModOp::Additive;
	Modifier.ModifierMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(InAmount));
	Modifiers.Add(Modifier);
}

void UGoddessGE_CustomEffect::ClearModifiers()
{
	if (!Modifiers.IsEmpty())
		Modifiers.Empty();
}
