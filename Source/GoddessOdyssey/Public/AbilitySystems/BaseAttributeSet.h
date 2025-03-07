// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "BaseAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UBaseAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category="Health")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, CurrentHealth)

	UPROPERTY(BlueprintReadOnly, Category="Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MaxHealth)
	
	UPROPERTY(BlueprintReadOnly, Category="Rage")
	FGameplayAttributeData CurrentRage;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, CurrentRage)

	UPROPERTY(BlueprintReadOnly, Category="Rage")
	FGameplayAttributeData MaxRage;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MaxRage)

	UPROPERTY(BlueprintReadOnly, Category="Damage")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, AttackPower)

	UPROPERTY(BlueprintReadOnly, Category="Damage")
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, DefensePower)
};
