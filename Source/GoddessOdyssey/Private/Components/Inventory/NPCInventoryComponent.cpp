// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Inventory/NPCInventoryComponent.h"

#include "DebugHelper.h"

void UNPCInventoryComponent::PrintSavedInventoryItemData()
{
	for (FGoddessSlotData Weapon : SavedInventoryItemData.Weapons)
	{
		Debug::Print(FString::Printf(TEXT("Weapon ID: %s, Quantity: %d"), *Weapon.ItemID.RowName.ToString(),
									 Weapon.Quantity));
	}

	for (FGoddessSlotData Shield : SavedInventoryItemData.Shields)
	{
		Debug::Print(FString::Printf(TEXT("Shield ID: %s, Quantity: %d"), *Shield.ItemID.RowName.ToString(),
									 Shield.Quantity));
	}

	for (FGoddessSlotData Eatable : SavedInventoryItemData.Eatables)
	{
		Debug::Print(FString::Printf(TEXT("Eatable ID: %s, Quantity: %d"), *Eatable.ItemID.RowName.ToString(),
									 Eatable.Quantity));
	}
}
