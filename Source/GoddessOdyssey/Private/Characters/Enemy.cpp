// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemy.h"

#include "Components/Combat/EnemyCombatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemy::AEnemy()
{
	// AI控制器
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false; // 禁用控制器（Controller）的期望旋转对角色运动方向的影响
	GetCharacterMovement()->bOrientRotationToMovement = true; // 启用角色的旋转方向始终与运动方向一致。
	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f,0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f; //设置角色在步行状态下的制动减速率

	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>(TEXT("EnemyCombatComponent"));
}
