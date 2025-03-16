// Fill out your copyright notice in the Description page of Project Settings.


#include "GoddessGameplayTags.h"


namespace GoddessGameplayTags
{
	/** Input Tags **/
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "Input.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "Input.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Equip, "Input.Equip");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UnEquip, "Input.UnEquip");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Roll, "Input.Roll");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_LightAttack_Sword, "Input.LightAttack.Sword");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_HeavyAttack_Sword, "Input.HeavyAttack.Sword");

	/** Goddess Tags**/
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Equip_Sword, "Character.Ability.Equip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_UnEquip_Sword, "Character.Ability.UnEquip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Attack_Light_Sword, "Character.Ability.Attack.Light.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Attack_Heavy_Sword, "Character.Ability.Attack.Heavy.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_HitPause, "Character.Ability.HitPause");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Roll, "Character.Ability.Roll");

	UE_DEFINE_GAMEPLAY_TAG(Character_Weapon_Sword, "Character.Weapon.Sword");

	UE_DEFINE_GAMEPLAY_TAG(Character_Event_Equip_Sword, "Character.Event.Equip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_UnEquip_Sword, "Character.Event.UnEquip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_Attack_End, "Character.Event.Attack.End");
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_HitPause, "Character.Event.HitPause");

	UE_DEFINE_GAMEPLAY_TAG(Character_Status_JumpToFinish, "Character.Status.JumpToFinish");
	UE_DEFINE_GAMEPLAY_TAG(Character_Status_Roll, "Character.Status.Roll");

	UE_DEFINE_GAMEPLAY_TAG(Character_SetByCaller_Attack_Light, "Character.SetByCaller.Attack.Light");
	UE_DEFINE_GAMEPLAY_TAG(Character_SetByCaller_Attack_Heavy, "Character.SetByCaller.Attack.Heavy");

	/** Enemy Tags**/
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee,"Enemy.Ability.Melee");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Ranged,"Enemy.Ability.Ranged");
	
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Weapon, "Enemy.Weapon");

	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Strafing, "Enemy.Status.Strafing");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_UnderAttack, "Enemy.Status.UnderAttack");

	/** Shared Tags**/
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact,"Shared.Ability.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Death,"Shared.Ability.Death");
	
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_MeleeAttack, "Shared.Event.MeleeAttack");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact,"Shared.Event.HitReact");

	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_BaseDamage, "Shared.SetByCaller.BaseDamage");
	
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Death, "Shared.Status.Death");
}
