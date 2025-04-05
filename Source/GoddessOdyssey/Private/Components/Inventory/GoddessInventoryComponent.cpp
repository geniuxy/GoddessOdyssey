// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Inventory/GoddessInventoryComponent.h"

UGoddessInventoryComponent::UGoddessInventoryComponent()
{
	InventoryItemData.Weapons.SetNum(5);
	InventoryItemData.Shields.SetNum(7);
	InventoryItemData.Eatables.SetNum(8);
}
