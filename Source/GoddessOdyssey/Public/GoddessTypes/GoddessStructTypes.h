// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameplayTagContainer.h"
#include "AbilitySystems/Abilities/GoddessGameplayAbility.h"

#include "GoddessStructTypes.generated.h"

class AInventoryItemBase;
class UGoddessGameplayAbility;
class UInputMappingContext;
class UGoddessLinkedAnimLayer;

USTRUCT(BlueprintType)
struct FGoddessAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(Categories = "Input"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGoddessGameplayAbility> AbilityToGrant;

	bool IsValid() const
	{
		return InputTag.IsValid() && AbilityToGrant;
	}
};

USTRUCT(BlueprintType)
struct FGoddessSpecialAbilitySet : public FGoddessAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UMaterialInterface> SoftAbilityIconMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(Categories = "Character.Cooldown"))
	FGameplayTag CooldownTag;
};

USTRUCT(BlueprintType)
struct FGoddessWeaponData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGoddessLinkedAnimLayer> WeaponAnimLayerToLink;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(TitleProperty = "InputTag"))
	TArray<FGoddessAbilitySet> DefaultWeaponAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(TitleProperty = "InputTag"))
	TArray<FGoddessSpecialAbilitySet> SpecialWeaponAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat WeaponBaseDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> SoftWeaponIconTexture;
};

USTRUCT(BlueprintType)
struct FGoddessMoneyData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMesh* Mesh;
};

USTRUCT(BlueprintType)
struct FGoddessItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Description;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> SoftItemThumbnail;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 StackSize;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Power;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMesh* ItemMesh;
};

USTRUCT(BlueprintType)
struct FGoddessSlotData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FDataTableRowHandle ItemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AInventoryItemBase> ItemClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Quantity = 0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EGoddessItemType ItemType;
};


USTRUCT(BlueprintType)
struct FGoddessInventoryItemData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FGoddessSlotData> Weapons;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FGoddessSlotData> Shields;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FGoddessSlotData> Eatables;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxWeaponSlotNum = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxShieldSlotNum = 7;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxEatableSlotNum = 8;
};
