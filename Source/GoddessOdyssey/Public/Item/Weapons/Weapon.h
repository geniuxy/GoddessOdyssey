// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class GODDESSODYSSEY_API AWeapon : public AItem
{
	GENERATED_BODY()

public:
	AWeapon();
	
	void Equip(USceneComponent* InParent, FName SocketName, AActor* NewOwner, APawn* NewInstigator);

	void AttachWeaponTo(USceneComponent* InParent, FName SocketName);

protected:

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* WeaponMesh;
	
};
