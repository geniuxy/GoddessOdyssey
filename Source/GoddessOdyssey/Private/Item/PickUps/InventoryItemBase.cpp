// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PickUps/InventoryItemBase.h"

#include "DebugHelper.h"
#include "AbilitySystems/BaseAbilitySystemComponent.h"
#include "Characters/Goddess.h"
#include "GoddessGameplayTags.h"

void AInventoryItemBase::AddToInventory(UDataTable* AllInventoryItemsDataTable,
                                        FGoddessInventoryItemData& CurrentInventoryItemData)
{
	if (!AllInventoryItemsDataTable) return;
	FGoddessItemData* FoundItemData =
		AllInventoryItemsDataTable->FindRow<FGoddessItemData>(InventoryItemSlotData.ItemID.RowName, TEXT(""));
	if (!FoundItemData) return;
	CachedFoundItemsStackSize = FoundItemData->StackSize;

	bool bWasAddedSuccessfully = false;
	switch (InventoryItemSlotData.ItemType)
	{
	case EGoddessItemType::Weapon:
		bWasAddedSuccessfully = TryAddItemToInventory(
			InventoryItemSlotData,
			CurrentInventoryItemData.Weapons,
			CurrentInventoryItemData.MaxWeaponSlotNum
		);
		break;
	case EGoddessItemType::Shield:
		bWasAddedSuccessfully = TryAddItemToInventory(
			InventoryItemSlotData,
			CurrentInventoryItemData.Shields,
			CurrentInventoryItemData.MaxShieldSlotNum
		);
		break;
	case EGoddessItemType::Eatable:
		bWasAddedSuccessfully = TryAddItemToInventory(
			InventoryItemSlotData,
			CurrentInventoryItemData.Eatables,
			CurrentInventoryItemData.MaxEatableSlotNum
		);
		break;
	default:
		break;
	}

	if (bWasAddedSuccessfully)
		Destroy();
	else
		Debug::Print(TEXT("Add to Inventory failed"));
}

bool AInventoryItemBase::TryAddItemToInventory(FGoddessSlotData& GoddessSlotData,
                                               TArray<FGoddessSlotData>& InGroup, int32 InMaxGroupSlotSize)
{
	if (CachedFoundItemsStackSize == -1 || GoddessSlotData.Quantity > CachedFoundItemsStackSize)
	{
		Debug::Print(TEXT("Some Wrong happened in the process of adding item to inventory"));
		return false;
	}

	for (FGoddessSlotData& Slot : InGroup) {
		if (Slot.ItemID == GoddessSlotData.ItemID) {
			int32 RemainingSpace = CachedFoundItemsStackSize - Slot.Quantity;
			if (RemainingSpace <= 0) continue;

			int32 AddedAmount = FMath::Min(GoddessSlotData.Quantity, RemainingSpace);
			Slot.Quantity += AddedAmount;
			GoddessSlotData.Quantity -= AddedAmount;
        
			if (GoddessSlotData.Quantity <= 0) {
				return true;
			}
		}
	}

	// 剩余未合并部分尝试新建槽位
	if (InGroup.Num() < InMaxGroupSlotSize) {
		InGroup.Add(GoddessSlotData);
		return true;
	}
	
	return false;
}

void AInventoryItemBase::OnPickUpCollisionSphereBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	Super::OnPickUpCollisionSphereBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep,
	                                           SweepResult);

	if (AGoddess* Goddess = Cast<AGoddess>(OtherActor))
	{
		Goddess->GetBaseAbilitySystemComponent()
		       ->TryActivateAbilityByTag(GoddessGameplayTags::Character_Ability_PickUp_InventoryItem);
	}
}
