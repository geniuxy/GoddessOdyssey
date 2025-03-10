// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/GEExecCalc/GEExecCalc_DamageTaken.h"
#include "AbilitySystems/BaseAttributeSet.h"
#include "GoddessGameplayTags.h"

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

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                     FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	FGameplayEffectSpec EffectSpec = ExecutionParams.GetOwningSpec();

	/*EffectSpec.GetContext().GetSourceObject();
	EffectSpec.GetContext().GetAbility();
	EffectSpec.GetContext().GetInstigator();
	EffectSpec.GetContext().GetEffectCauser();*/

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetBaseDamageCapture().AttackPowerDef,
	                                                           EvaluateParameters, SourceAttackPower);

	float BaseDamge = 0.f;
	int32 UsedLightAttackComboCount = 0;
	int32 UsedHeavyAttackComboCount = 0;
	for (const TPair<FGameplayTag, float> TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(GoddessGameplayTags::Shared_SetByCaller_BaseDamage))
			BaseDamge = TagMagnitude.Value;
		
		if (TagMagnitude.Key.MatchesTagExact(GoddessGameplayTags::Character_SetByCaller_Attack_Light))
			UsedLightAttackComboCount = TagMagnitude.Value;
			
		if (TagMagnitude.Key.MatchesTagExact(GoddessGameplayTags::Character_SetByCaller_Attack_Heavy))
			UsedHeavyAttackComboCount = TagMagnitude.Value;
	}

	float SourceDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetBaseDamageCapture().DefensePowerDef,
															   EvaluateParameters, SourceDefensePower);
	
}
