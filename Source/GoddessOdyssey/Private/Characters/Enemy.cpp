// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemy.h"

#include "DebugHelper.h"
#include "GoddessFunctionLibrary.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "Components/UI/EnemyUIComponent.h"
#include "DataAssets/StartUpData/DataAsset_StartUpData.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Widgets/BaseWidget.h"

AEnemy::AEnemy()
{
	// AI控制器
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false; // 禁用控制器（Controller）的期望旋转对角色运动方向的影响
	GetCharacterMovement()->bOrientRotationToMovement = true; // 启用角色的旋转方向始终与运动方向一致。
	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f; //设置角色在步行状态下的制动减速率

	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>(TEXT("EnemyCombatComponent"));

	EnemyUIComponent = CreateDefaultSubobject<UEnemyUIComponent>(TEXT("EnemyUIComponent"));

	EnemyHealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("EnemyHealthWidgetComponent"));
	EnemyHealthWidgetComponent->SetupAttachment(GetMesh());

	UnBlockableAttackWarningComponent = CreateDefaultSubobject<USceneComponent>(TEXT("UnBlockableAttackWarningComp"));
	UnBlockableAttackWarningComponent->SetupAttachment(GetMesh());

	LeftHandCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftHandCollisionBox"));
	LeftHandCollisionBox->SetupAttachment(GetMesh());
	LeftHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftHandCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &AEnemy::OnBodyCollisionBoxBeginOverlap);

	RightHandCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RightHandCollisionBox"));
	RightHandCollisionBox->SetupAttachment(GetMesh());
	RightHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightHandCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &AEnemy::OnBodyCollisionBoxBeginOverlap);
}

UBaseCombatComponent* AEnemy::GetCombatComponentByInterface() const
{
	return EnemyCombatComponent;
}

UBaseUIComponent* AEnemy::GetUIComponentByInterface() const
{
	return EnemyUIComponent;
}

UEnemyUIComponent* AEnemy::GetEnemyUIComponentByInterface() const
{
	return EnemyUIComponent;
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (UBaseWidget* Widget = Cast<UBaseWidget>(EnemyHealthWidgetComponent->GetUserWidgetObject()))
		Widget->InitEnemyCreatedWidget(this);
}

void AEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitEnemyStartUpData();
}

#if WITH_EDITOR
void AEnemy::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(
		ThisClass, LeftHandCollisionBoxAttachBoneName))
	{
		LeftHandCollisionBox->AttachToComponent(
			GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			LeftHandCollisionBoxAttachBoneName
		);
	}

	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(
		ThisClass, RightHandCollisionBoxAttachBoneName))
	{
		RightHandCollisionBox->AttachToComponent(
			GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			RightHandCollisionBoxAttachBoneName
		);
	}
}
#endif

void AEnemy::OnBodyCollisionBoxBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (UGoddessFunctionLibrary::IsTargetPawnHostile(this, HitPawn))
			EnemyCombatComponent->OnHitTargetActor(HitPawn);
	}
}

void AEnemy::InitEnemyStartUpData()
{
	if (CharacterStartUpData.IsNull()) return;

	// 异步加载，不占用主线程
	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this]()
			{
				if (UDataAsset_StartUpData* LoadedData = CharacterStartUpData.Get())
					LoadedData->GiveToAbilitySystemComponent(BaseAbilitySystemComponent, GetCurrentAbilityApplyLevel());
			}
		)
	);
}
