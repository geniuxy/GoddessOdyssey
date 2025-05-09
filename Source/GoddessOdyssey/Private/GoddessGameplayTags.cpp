// Fill out your copyright notice in the Description page of Project Settings.


#include "GoddessGameplayTags.h"


namespace GoddessGameplayTags
{
	/** Input Tags **/
	UE_DEFINE_GAMEPLAY_TAG(Input_Move, "Input.Move");
	UE_DEFINE_GAMEPLAY_TAG(Input_Look, "Input.Look");
	UE_DEFINE_GAMEPLAY_TAG(Input_Climb, "Input.Climb");
	UE_DEFINE_GAMEPLAY_TAG(Input_ClimbMove, "Input.ClimbMove");
	UE_DEFINE_GAMEPLAY_TAG(Input_ClimbHop, "Input.ClimbHop");
	UE_DEFINE_GAMEPLAY_TAG(Input_Equip, "Input.Equip");
	UE_DEFINE_GAMEPLAY_TAG(Input_UnEquip, "Input.UnEquip");
	UE_DEFINE_GAMEPLAY_TAG(Input_Roll, "Input.Roll");
	UE_DEFINE_GAMEPLAY_TAG(Input_LightAttack_Sword, "Input.LightAttack.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Input_HeavyAttack_Sword, "Input.HeavyAttack.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Input_SwitchTarget, "Input.SwitchTarget");
	UE_DEFINE_GAMEPLAY_TAG(Input_SpecialWeaponAbility_Light, "Input.SpecialWeaponAbility.Light");
	UE_DEFINE_GAMEPLAY_TAG(Input_SpecialWeaponAbility_Heavy, "Input.SpecialWeaponAbility.Heavy");
	UE_DEFINE_GAMEPLAY_TAG(Input_PickUp_Stone, "Input.PickUp.Stone");
	UE_DEFINE_GAMEPLAY_TAG(Input_PickUp_InventoryItem, "Input.PickUp.InventoryItem");
	UE_DEFINE_GAMEPLAY_TAG(Input_Enter_Shop, "Input.Enter.Shop");

	UE_DEFINE_GAMEPLAY_TAG(Input_MustBeHeld, "Input.MustBeHeld");
	UE_DEFINE_GAMEPLAY_TAG(Input_MustBeHeld_Block, "Input.MustBeHeld.Block");

	UE_DEFINE_GAMEPLAY_TAG(Input_Toggleable, "Input.Toggleable");
	UE_DEFINE_GAMEPLAY_TAG(Input_Toggleable_TargetLock, "Input.Toggleable.TargetLock");
	UE_DEFINE_GAMEPLAY_TAG(Input_Toggleable_Rage, "Input.Toggleable.Rage");
	UE_DEFINE_GAMEPLAY_TAG(Input_Toggleable_UI_Inventory, "Input.Toggleable.UI.Inventory");

	/** Goddess Tags**/
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Equip_Sword, "Character.Ability.Equip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Equip_Weapon, "Character.Ability.Equip.Weapon");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_UnEquip_Sword, "Character.Ability.UnEquip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_UnEquip_Weapon, "Character.Ability.UnEquip.Weapon");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Attack_Light_Sword, "Character.Ability.Attack.Light.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Attack_Heavy_Sword, "Character.Ability.Attack.Heavy.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_HitPause, "Character.Ability.HitPause");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Roll, "Character.Ability.Roll");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Block, "Character.Ability.Block");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_TargetLock, "Character.Ability.TargetLock");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Rage, "Character.Ability.Rage");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_SpecialWeaponAbility_Light,
	                       "Character.Ability.SpecialWeaponAbility.Light");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_SpecialWeaponAbility_Heavy,
	                       "Character.Ability.SpecialWeaponAbility.Heavy");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Inventory, "Character.Ability.Inventory");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_PickUp_Stone, "Character.Ability.PickUp.Stone");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_PickUp_Money, "Character.Ability.PickUp.Money");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_PickUp_InventoryItem, "Character.Ability.PickUp.InventoryItem");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Enter_Shop, "Character.Ability.Enter.Shop");

	UE_DEFINE_GAMEPLAY_TAG(Character_Cooldown_SpecialWeaponAbility_Light,
	                       "Character.Cooldown.SpecialWeaponAbility.Light");
	UE_DEFINE_GAMEPLAY_TAG(Character_Cooldown_SpecialWeaponAbility_Heavy,
	                       "Character.Cooldown.SpecialWeaponAbility.Heavy");

	UE_DEFINE_GAMEPLAY_TAG(Character_Weapon_Sword_LJL, "Character.Weapon.Sword.LJL");
	UE_DEFINE_GAMEPLAY_TAG(Character_Weapon_Sword_Board, "Character.Weapon.Sword.Board");
	UE_DEFINE_GAMEPLAY_TAG(Character_Weapon_Hammer, "Character.Weapon.Hammer");
	UE_DEFINE_GAMEPLAY_TAG(Character_Weapon_BlizardRod, "Character.Weapon.BlizardRod");
	UE_DEFINE_GAMEPLAY_TAG(Character_Shield_DayBreaker, "Character.Shield.DayBreaker");
	UE_DEFINE_GAMEPLAY_TAG(Character_Shield_RoyalGuard, "Character.Shield.RoyalGuard");
	UE_DEFINE_GAMEPLAY_TAG(Character_Shield_SteelLizal, "Character.Shield.SteelLizal");

	UE_DEFINE_GAMEPLAY_TAG(Character_Event_Equip_Sword, "Character.Event.Equip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_UnEquip, "Character.Event.UnEquip");
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_UnEquip_Sword, "Character.Event.UnEquip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_Attack_End, "Character.Event.Attack.End");
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_HitPause, "Character.Event.HitPause");
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_SuccessfulBlock, "Character.Event.SuccessfulBlock");
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_SwitchTarget_Left, "Character.Event.SwitchTarget.Left");
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_SwitchTarget_Right, "Character.Event.SwitchTarget.Right");
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_ActivateRage, "Character.Event.ActivateRage");
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_SaveInventoryItems, "Character.Event.SaveInventoryItems");
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_ConsumeStones, "Character.Event.ConsumeStones");
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_ConsumeMoney, "Character.Event.ConsumeMoney");
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_ToggleInventory, "Character.Event.ToggleInventory");
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_Enter_Shop, "Character.Event.Enter.Shop");

	UE_DEFINE_GAMEPLAY_TAG(Character_Status_JumpToFinish, "Character.Status.JumpToFinish");
	UE_DEFINE_GAMEPLAY_TAG(Character_Status_Parry, "Character.Status.Parry");
	UE_DEFINE_GAMEPLAY_TAG(Character_Status_Rolling, "Character.Status.Rolling");
	UE_DEFINE_GAMEPLAY_TAG(Character_Status_Blocking, "Character.Status.Blocking");
	UE_DEFINE_GAMEPLAY_TAG(Character_Status_TargetLock, "Character.Status.TargetLock");
	UE_DEFINE_GAMEPLAY_TAG(Character_Status_Rage_Activating, "Character.Status.Rage.Activating");
	UE_DEFINE_GAMEPLAY_TAG(Character_Status_Rage_Active, "Character.Status.Rage.Active");
	UE_DEFINE_GAMEPLAY_TAG(Character_Status_Rage_Full, "Character.Status.Rage.Full");
	UE_DEFINE_GAMEPLAY_TAG(Character_Status_Rage_None, "Character.Status.Rage.None");

	UE_DEFINE_GAMEPLAY_TAG(Character_SetByCaller_Attack_Light, "Character.SetByCaller.Attack.Light");
	UE_DEFINE_GAMEPLAY_TAG(Character_SetByCaller_Attack_Heavy, "Character.SetByCaller.Attack.Heavy");
	UE_DEFINE_GAMEPLAY_TAG(Character_SetByCaller_ShieldPower, "Character.SetByCaller.ShieldPower");

	/** Enemy Tags**/
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee, "Enemy.Ability.Melee");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Ranged, "Enemy.Ability.Ranged");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_SummonEnemies, "Enemy.Ability.SummonEnemies");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Spawn_Stone, "Enemy.Ability.Spawn.Stone");

	UE_DEFINE_GAMEPLAY_TAG(Enemy_Weapon, "Enemy.Weapon");

	UE_DEFINE_GAMEPLAY_TAG(Enemy_Event_SummonEnemies, "Enemy.Event.SummonEnemies");

	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Strafing, "Enemy.Status.Strafing");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_UnderAttack, "Enemy.Status.UnderAttack");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_UnBlockable, "Enemy.Status.UnBlockable");

	/** Shared Tags**/
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact, "Shared.Ability.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Death, "Shared.Ability.Death");

	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_MeleeAttack, "Shared.Event.MeleeAttack");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact, "Shared.Event.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_SpawnProjectile, "Shared.Event.SpawnProjectile");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_AOE, "Shared.Event.AOE");

	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_BaseDamage, "Shared.SetByCaller.BaseDamage");

	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Death, "Shared.Status.Death");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Front, "Shared.Status.HitReact.Front");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Left, "Shared.Status.HitReact.Left");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Right, "Shared.Status.HitReact.Right");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Back, "Shared.Status.HitReact.Back");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Invincible, "Shared.Status.Invincible");

	/** Game Data tags **/
	UE_DEFINE_GAMEPLAY_TAG(GameData_Level_SurvivalGameModeMap, "GameData.Level.SurvivalGameModeMap");
	UE_DEFINE_GAMEPLAY_TAG(GameData_Level_MainMenuMap, "GameData.Level.MainMenuMap");
	
	UE_DEFINE_GAMEPLAY_TAG(GameData_SaveGame_Slot_1, "GameData.SaveGame.Slot.1");
}
