// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/BaseAttributeSet.h"

UBaseAttributeSet::UBaseAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitCurrentRage(1.f);
	InitMaxRage(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
}
