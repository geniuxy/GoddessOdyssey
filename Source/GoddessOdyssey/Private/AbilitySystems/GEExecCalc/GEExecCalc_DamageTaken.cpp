// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/GEExecCalc/GEExecCalc_DamageTaken.h"
#include "AbilitySystems/BaseAttributeSet.h"

struct FBaseDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)

	FBaseDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, AttackPower, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, DefensePower, Target, false)
	}
};

static const FBaseDamageCapture& GetBaseDamageCapture()
{
	static FBaseDamageCapture BaseDamageCapture;
	return BaseDamageCapture;
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	/** Slow way of doing capture */
	//FProperty* AttackPowerProperty = FindFieldChecked<FProperty>(
	//	UWarriorAttributeSet::StaticClass(),
	//	GET_MEMBER_NAME_CHECKED(UWarriorAttributeSet,AttackPower)
	//);

	//FGameplayEffectAttributeCaptureDefinition AttackPowerCaptureDefinition(
	//	AttackPowerProperty,
	//	EGameplayEffectAttributeCaptureSource::Source,
	//	false
	//);

	//RelevantAttributesToCapture.Add(AttackPowerCaptureDefinition);

	/** fast way of doing capture */
	RelevantAttributesToCapture.Add(GetBaseDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetBaseDamageCapture().DefensePowerDef);
}
