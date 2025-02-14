// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Goddess.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Characters/GoddessType.h"
#include "Item/Weapons/Weapon.h"

AGoddess::AGoddess()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AGoddess::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
}

void AGoddess::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AGoddess::CanAttack()
{
	return ActionState == EGoddessActionState::EGAS_UnOccupied &&
		EquippedState != EGoddessEquippedState::EGES_UnEquipped;
}

void AGoddess::FinishAttack()
{
	ActionState = EGoddessActionState::EGAS_UnOccupied;
}

void AGoddess::Attack()
{
	if (CanAttack())
	{
		PlayAttackMontage();
		ActionState = EGoddessActionState::EGAS_Attacking;
	}
}

void AGoddess::Equip()
{
	AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem);
	if (OverlappingWeapon)
	{
		OverlappingWeapon->Equip(GetMesh(), FName("RightHandSocket"), this, this);
		EquippedState = EGoddessEquippedState::EGES_EquippedOneHandedWeapon;
		EquippedWeapon = OverlappingWeapon;
		OverlappingItem = nullptr;
	}
}

void AGoddess::PlayAttackMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && AttackMontage)
	{
		AnimInstance->Montage_Play(AttackMontage);
		const float CurrentTime = GetWorld()->GetTimeSeconds();

		// check combo attack
		if (CurrentTime - LastAttackTime < AttackComboWindow)
			AttackCount = (AttackCount + 1) % ComboCount;
		else
			AttackCount = 0;
		LastAttackTime = CurrentTime;

		// 打印last attack time
		UE_LOG(LogTemp, Warning, TEXT("LastAttackTime: %f"), LastAttackTime);
		// 打印当前攻击次数
		UE_LOG(LogTemp, Warning, TEXT("AttackCount: %d"), AttackCount);

		FName SectionName = FName(*FString::Printf(TEXT("Attack%d"), AttackCount+1));

		AnimInstance->Montage_JumpToSection(SectionName, AttackMontage);
	}
}

void AGoddess::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(EquipAction, ETriggerEvent::Triggered, this, &AGoddess::Equip);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AGoddess::Attack);
	}
}
