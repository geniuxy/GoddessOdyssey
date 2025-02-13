#pragma once

UENUM(BlueprintType)
enum class EGoddessActionState : uint8
{
	EGAS_UnOccupied UMETA(DisplayName = "UnOccupied"),
	EGAS_Attacking UMETA(DisplayName = "Attacking"),
	EGAS_Equipping UMETA(DisplayName = "Equipping")
};

UENUM(BlueprintType)
enum class EGoddessEquippedState : uint8
{
	EGES_UnEquipped UMETA(DisplayName = "UnEquipped"),
	EGES_EquippedOneHandedWeapon UMETA(DisplayName = "Equip One-Handed Weapon"),
	EGES_EquippedTwoHandedWeapon UMETA(DisplayName = "Equip Two-Handed Weapon"),
};