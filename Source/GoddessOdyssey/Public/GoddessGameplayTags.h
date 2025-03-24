// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "NativeGameplayTags.h"

namespace GoddessGameplayTags
{
	/** Input Tags **/
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Move);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Look);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Equip);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_UnEquip);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Roll);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_LightAttack_Sword);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_HeavyAttack_Sword);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_SwitchTarget);
	
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_MustBeHeld);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_MustBeHeld_Block);

	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Toggleable);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Toggleable_TargetLock);
	
	/** Goddess Tags**/
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Ability_Equip_Sword);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Ability_UnEquip_Sword);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Ability_Attack_Light_Sword);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Ability_Attack_Heavy_Sword);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Ability_HitPause);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Ability_Roll);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Ability_Block);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Ability_TargetLock);

	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Weapon_Sword);

	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Event_Equip_Sword);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Event_UnEquip_Sword);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Event_Attack_End);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Event_HitPause);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Event_SuccessfulBlock);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Event_SwitchTarget_Left);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Event_SwitchTarget_Right);

	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Status_JumpToFinish);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Status_Parry);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Status_Rolling);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Status_Blocking);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Status_TargetLock);

	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_SetByCaller_Attack_Light);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_SetByCaller_Attack_Heavy);

	/** Enemy Tags**/
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Ranged);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_SummonEnemies);
	
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon);
	
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Event_SummonEnemies);

	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_Strafing);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_UnderAttack);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_UnBlockable);

	/** Shared Tags**/
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_HitReact);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_Death);
	
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_MeleeAttack);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_HitReact);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_SpawnProjectile);

	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_BaseDamage);
	
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_Death);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Front);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Left);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Right);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Back);
}
