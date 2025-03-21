// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ProjectileBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "DebugHelper.h"
#include "GoddessFunctionLibrary.h"
#include "GoddessGameplayTags.h"
#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ProjectileBoxComponent"));
	SetRootComponent(ProjectileBoxComponent);
	ProjectileBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProjectileBoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	ProjectileBoxComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	ProjectileBoxComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	ProjectileBoxComponent->OnComponentHit.AddUniqueDynamic(this, &AProjectileBase::OnProjectileHit);
	ProjectileBoxComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AProjectileBase::OnProjectileBeginOverlap);

	ProjectileNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileNiagaraComponent"));
	ProjectileNiagaraComponent->SetupAttachment(GetRootComponent());

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComp->InitialSpeed = 500.f;
	ProjectileMovementComp->MaxSpeed = 500.f;
	ProjectileMovementComp->Velocity = FVector(1.f, 0.f, 0.f);
	ProjectileMovementComp->ProjectileGravityScale = 0.f;

	InitialLifeSpan = 4.f;
}

void AProjectileBase::OnProjectileHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	BP_OnSpawnProjectileHitFX(Hit.ImpactPoint);

	APawn* HitPawn = Cast<APawn>(OtherActor);
	if (!HitPawn || !UGoddessFunctionLibrary::IsTargetPawnHostile(GetInstigator(), HitPawn))
	{
		Destroy();
		return;
	}

	bool bIsValidBlock = false;

	const bool bIsPlayerBlocking =
		UGoddessFunctionLibrary::NativeDoesActorHaveTag(HitPawn, GoddessGameplayTags::Character_Status_Blocking);

	if (bIsPlayerBlocking)
		bIsValidBlock = UGoddessFunctionLibrary::IsValidBlock(this, HitPawn);

	FGameplayEventData Data;
	Data.Instigator = this;
	Data.Target = HitPawn;

	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitPawn,
			GoddessGameplayTags::Character_Event_SuccessfulBlock,
			Data
		);
	}
	else
	{
		HandleApplyProjectileDamage(HitPawn, Data);
	}

	Destroy();
}

void AProjectileBase::OnProjectileBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	if (ProjectileDamagePolicy == EProjectileDamagePolicy::OnBeginOverlay)
		ProjectileBoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AProjectileBase::HandleApplyProjectileDamage(APawn* InHitPawn, const FGameplayEventData& InPayLoad)
{
	checkf(ProjectileDamageEffectSpecHandle.IsValid(),
	       TEXT("Forgot to assign a valid spec handle to the projectile: %s"), *GetActorNameOrLabel());
	
	bool bWasApplied = UGoddessFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(
		GetInstigator(), InHitPawn, ProjectileDamageEffectSpecHandle);
	if (bWasApplied)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			this,
			GoddessGameplayTags::Shared_Event_HitReact,
			InPayLoad
		);
	}
}
