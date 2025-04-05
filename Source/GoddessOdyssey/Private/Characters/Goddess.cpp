// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Goddess.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GoddessGameplayTags.h"
#include "Camera/CameraComponent.h"
#include "Characters/GoddessType.h"
#include "Components/CapsuleComponent.h"
#include "Components/Input/GoddessInputComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "GameFramework/SpringArmComponent.h"
#include "Item/Weapons/Weapon.h"
#include "DebugHelper.h"
#include "AbilitySystems/BaseAbilitySystemComponent.h"
#include "Components/Combat/GoddessCombatComponent.h"
#include "Components/Inventory/GoddessInventoryComponent.h"
#include "Components/UI/GoddessUIComponent.h"
#include "DataAssets/StartUpData/DataAsset_StartUpData.h"

AGoddess::AGoddess()
{
	GetCapsuleComponent()->InitCapsuleSize(34.f, 88.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	WeaponFloatSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Weapon Float SpringArm"));
	WeaponFloatSpringArm->SetupAttachment(GetRootComponent());
	WeaponFloatSpringArm->AddLocalOffset(FVector(0.f, 0.f, 80.f));
	WeaponFloatSpringArm->TargetArmLength = 45.0f;
	WeaponFloatSpringArm->bEnableCameraLag = true;
	WeaponFloatSpringArm->bEnableCameraRotationLag = true;

	WeaponPosition = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Position"));
	WeaponPosition->SetupAttachment(WeaponFloatSpringArm);
	WeaponPosition->SetRelativeRotation(FRotator(340.f, 90.f, 0.f));

	GoddessCombatComponent = CreateDefaultSubobject<UGoddessCombatComponent>(TEXT("GoddessCombatComponent"));
	GoddessUIComponent = CreateDefaultSubobject<UGoddessUIComponent>(TEXT("GoddessUIComponent"));
	GoddessInventoryComponent = CreateDefaultSubobject<UGoddessInventoryComponent>(TEXT("GoddessInventoryComponent"));
}

UBaseCombatComponent* AGoddess::GetCombatComponentByInterface() const
{
	return GoddessCombatComponent;
}

UBaseUIComponent* AGoddess::GetUIComponentByInterface() const
{
	return GoddessUIComponent;
}

UGoddessUIComponent* AGoddess::GetGoddessUIComponentByInterface() const
{
	return GoddessUIComponent;
}

void AGoddess::BeginPlay()
{
	Super::BeginPlay();

	// InitFloatingWeapon();
}

void AGoddess::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_StartUpData* StartUpData = CharacterStartUpData.LoadSynchronous())
			StartUpData->GiveToAbilitySystemComponent(BaseAbilitySystemComponent, GetCurrentAbilityApplyLevel());
	}
}

void AGoddess::CallBack_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MoveVector = InputActionValue.Get<FVector2D>();

	// 获取角色控制器的偏航角（Yaw），并将其转换为一个旋转值（FRotator）。
	// 偏航角是角色在水平方向上的旋转角度，用于确定角色的朝向
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

	if (MoveVector.Y != 0.f)
	{
		// MovementRotation.RotateVector() 被用来将标准方向向量（如 FVector::ForwardVector 或 FVector::RightVector）旋转到角色的当前朝向。
		const FVector ForwardVector = MovementRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardVector, MoveVector.Y);
	}

	if (MoveVector.X != 0.f)
	{
		const FVector RightVector = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightVector, MoveVector.X);
	}
}

void AGoddess::CallBack_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (LookAxisVector.Y != 0.f)
		AddControllerPitchInput(LookAxisVector.Y);

	if (LookAxisVector.X != 0.f)
		AddControllerYawInput(LookAxisVector.X);
}

void AGoddess::CallBack_SwitchTargetTriggered(const FInputActionValue& InputActionValue)
{
	TargetSwitchDirection = InputActionValue.Get<FVector2D>();
}

void AGoddess::CallBack_SwitchTargetCompleted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;
	FGameplayTag SendTag = TargetSwitchDirection.X > 0.f
		                       ? GoddessGameplayTags::Character_Event_SwitchTarget_Right
		                       : GoddessGameplayTags::Character_Event_SwitchTarget_Left;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, SendTag, Data);

	// Debug::Print("Switch Direction: " + SendTag.ToString());
}

void AGoddess::CallBack_PickUpStoneStarted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		GoddessGameplayTags::Character_Event_ConsumeStones,
		Data
	);
}

void AGoddess::CallBack_ToggleInventory(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		GoddessGameplayTags::Character_Event_ToggleInventory,
		Data
	);
}

void AGoddess::CallBack_AbilityInputPressed(FGameplayTag InInputTag)
{
	BaseAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void AGoddess::CallBack_AbilityInputReleased(FGameplayTag InInputTag)
{
	BaseAbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}

// void AGoddess::InitFloatingWeapon()
// {
// 	UWorld* World = GetWorld();
// 	if (World)
// 	{
// 		FActorSpawnParameters SpawnParams;
// 		SpawnParams.Owner = this;
// 		SpawnParams.Instigator = this;
//
// 		FloatingWeapon = World->SpawnActor<AWeapon>(FloatingWeaponClass, WeaponPosition->GetComponentLocation(),
// 		                                            WeaponPosition->GetComponentRotation(), SpawnParams);
// 		// 附加到武器位置，并且设置为保持场景位置
// 		FloatingWeapon->AttachToComponent(WeaponPosition, FAttachmentTransformRules::KeepWorldTransform);
// 	}
// }

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
	// else
	// 	WeaponAttachToHandEvent();
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

		FName SectionName = FName(*FString::Printf(TEXT("Attack%d"), AttackCount + 1));

		AnimInstance->Montage_JumpToSection(SectionName, AttackMontage);
	}
}

void AGoddess::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data asset as input config"));
	// 添加MappingContext
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(Subsystem);
	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	// Bind InputActions
	UGoddessInputComponent* GoddessInputComponent = CastChecked<UGoddessInputComponent>(PlayerInputComponent);
	GoddessInputComponent->BindNativeInputAction(InputConfigDataAsset, GoddessGameplayTags::Input_Move,
	                                             ETriggerEvent::Triggered, this, &ThisClass::CallBack_Move);
	GoddessInputComponent->BindNativeInputAction(InputConfigDataAsset, GoddessGameplayTags::Input_Look,
	                                             ETriggerEvent::Triggered, this, &ThisClass::CallBack_Look);

	GoddessInputComponent->BindNativeInputAction(InputConfigDataAsset, GoddessGameplayTags::Input_SwitchTarget,
	                                             ETriggerEvent::Triggered, this,
	                                             &ThisClass::CallBack_SwitchTargetTriggered);
	GoddessInputComponent->BindNativeInputAction(InputConfigDataAsset, GoddessGameplayTags::Input_SwitchTarget,
	                                             ETriggerEvent::Completed, this,
	                                             &ThisClass::CallBack_SwitchTargetCompleted);

	GoddessInputComponent->BindNativeInputAction(InputConfigDataAsset, GoddessGameplayTags::Input_PickUp_Stone,
	                                             ETriggerEvent::Started, this,
	                                             &ThisClass::CallBack_PickUpStoneStarted);

	GoddessInputComponent->BindNativeInputAction(InputConfigDataAsset, GoddessGameplayTags::Input_Toggleable_UI_Inventory,
												 ETriggerEvent::Started, this,
												 &ThisClass::CallBack_ToggleInventory);

	GoddessInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::CallBack_AbilityInputPressed,
	                                              &ThisClass::CallBack_AbilityInputReleased);

	// if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	// {
	// 	EnhancedInputComponent->BindAction(EquipAction, ETriggerEvent::Triggered, this, &AGoddess::Equip);
	// 	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AGoddess::Attack);
	// }
}
