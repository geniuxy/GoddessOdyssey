// Fill out your copyright notice in the Description page of Project Settings.


#include "GoddessGameplayTags.h"


namespace GoddessGameplayTags
{
	/** Input Tags **/
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "Input.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "Input.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Equip, "Input.Equip");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UnEquip, "Input.UnEquip");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_LightAttack_Sword, "Input.LightAttack.Sword");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_HeavyAttack_Sword, "Input.HeavyAttack.Sword");

	/** Goddess Tags**/
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Equip_Sword, "Character.Ability.Equip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_UnEquip_Sword, "Character.Ability.UnEquip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Attack_Light_Sword, "Character.Ability.Attack.Light.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Attack_Heavy_Sword, "Character.Ability.Attack.Heavy.Sword");
	
	UE_DEFINE_GAMEPLAY_TAG(Character_Weapon_Sword, "Character.Weapon.Sword");
	
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_Equip_Sword, "Character.Event.Equip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_UnEquip_Sword, "Character.Event.UnEquip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_Attack_End, "Character.Event.Attack.End");
	
	UE_DEFINE_GAMEPLAY_TAG(Character_Status_JumpToFinish, "Character.Status.JumpToFinish");

	/** Enemy Tags**/
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Weapon, "Enemy.Weapon");

	/** Shared Tags**/
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_MeleeAttack, "Shared.Event.MeleeAttack");
	
}
