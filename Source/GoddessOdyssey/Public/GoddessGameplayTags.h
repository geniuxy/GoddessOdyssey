// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "NativeGameplayTags.h"

namespace GoddessGameplayTags
{
	/** Input Tags **/
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Equip);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnEquip);

	/** Character Tags**/
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Ability_Equip_Sword);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Ability_UnEquip_Sword);

	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Weapon_Sword);

	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Event_Equip_Sword);
	GODDESSODYSSEY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Event_UnEquip_Sword);
}
