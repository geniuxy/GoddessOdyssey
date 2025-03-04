// Fill out your copyright notice in the Description page of Project Settings.


#include "GoddessGameplayTags.h"


namespace GoddessGameplayTags
{
	/** Input Tags **/
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "Input.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "Input.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Equip, "Input.Equip");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UnEquip, "Input.UnEquip");

	/** Character Tags**/
	UE_DEFINE_GAMEPLAY_TAG(Character_Weapon_Sword, "Character.Weapon.Sword");
	
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_Equip_Sword, "Character.Event.Equip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_UnEquip_Sword, "Character.Event.UnEquip.Sword");
}
