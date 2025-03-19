// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/Abilities/GoddessGA_TargetLock.h"

#include "GoddessFunctionLibrary.h"
#include "GoddessGameplayTags.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Characters/Goddess.h"
#include "Components/SizeBox.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PlayerControllers/GoddessController.h"
#include "Widgets/BaseWidget.h"

void UGoddessGA_TargetLock::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	TryLockOnTarget();
	InitTargetLockMovement();

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGoddessGA_TargetLock::EndAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility,
	bool bWasCancelled)
{
	ResetTargetLockMovement();
	CleanUp();

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGoddessGA_TargetLock::OnTargetLockTick(float DeltaTime)
{
	const bool bCanLockTarget = CurrentLockedActor &&
		!UGoddessFunctionLibrary::NativeDoesActorHaveTag(CurrentLockedActor, GoddessGameplayTags::Shared_Status_Death)
		&&
		!UGoddessFunctionLibrary::NativeDoesActorHaveTag(GetGoddessFromActorInfo(),
		                                                 GoddessGameplayTags::Shared_Status_Death);
	if (!bCanLockTarget)
	{
		CancelTargetLockAbility();
		return;
	}

	SetTargetLockWidgetPosition();

	const bool bShouldOverrideRotation =
		!UGoddessFunctionLibrary::NativeDoesActorHaveTag(GetGoddessFromActorInfo(),
		                                                 GoddessGameplayTags::Character_Status_Blocking) &&
		!UGoddessFunctionLibrary::NativeDoesActorHaveTag(GetGoddessFromActorInfo(),
		                                                 GoddessGameplayTags::Character_Status_Rolling);

	if (bShouldOverrideRotation)
	{
		const FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(
			GetGoddessFromActorInfo()->GetActorLocation(),
			CurrentLockedActor->GetActorLocation()
		);

		const FRotator CurrentControlRot = GetGoddessControllerFromActorInfo()->GetControlRotation();
		const FRotator TargetRot =
			FMath::RInterpTo(CurrentControlRot, LookAtRot, DeltaTime, TargetLockRotationInterpSpeed);

		GetGoddessControllerFromActorInfo()->SetControlRotation(FRotator(TargetRot.Pitch, TargetRot.Yaw, 0.f));
		GetGoddessFromActorInfo()->SetActorRotation(FRotator(0.f, TargetRot.Yaw, 0.f));
	}
}

void UGoddessGA_TargetLock::TryLockOnTarget()
{
	GetAvailableActorsToLock();

	if (AvailableActorsToLock.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}

	CurrentLockedActor = GetNearestTargetFromAvailableActors(AvailableActorsToLock);

	if (CurrentLockedActor)
	{
		CreateTargetLockPointer();

		SetTargetLockWidgetPosition();
	}
	else
		CancelTargetLockAbility();
}

void UGoddessGA_TargetLock::GetAvailableActorsToLock()
{
	AGoddess* Goddess = GetGoddessFromActorInfo();

	TArray<FHitResult> BoxTraceHits;

	UKismetSystemLibrary::BoxTraceMultiForObjects(
		Goddess,
		Goddess->GetActorLocation(),
		Goddess->GetActorLocation() + Goddess->GetActorForwardVector() * BoxTraceDistance,
		TraceBoxSize / 2.f,
		Goddess->GetActorForwardVector().ToOrientationRotator(),
		BoxTraceChannels,
		false,
		TArray<AActor*>(),
		bShowPersistentDebugShape ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
		BoxTraceHits,
		true
	);

	for (const FHitResult& TraceHit : BoxTraceHits)
	{
		if (AActor* HitActor = TraceHit.GetActor())
		{
			if (HitActor != Goddess)
				AvailableActorsToLock.AddUnique(HitActor);
		}
	}
}

AActor* UGoddessGA_TargetLock::GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors)
{
	float Distance = 0.f;
	return UGameplayStatics::FindNearestActor(
		GetGoddessFromActorInfo()->GetActorLocation(), InAvailableActors, Distance);
}

void UGoddessGA_TargetLock::CreateTargetLockPointer()
{
	if (!DrawnTargetLockWidget)
	{
		checkf(TargetLockWidgetClass, TEXT("Forgot to assign a valid widget class in Blueprint"));
		// 这里注意要在include里加上Controller的h头文件，不然会报错
		DrawnTargetLockWidget = CreateWidget<UBaseWidget>(GetGoddessControllerFromActorInfo(), TargetLockWidgetClass);

		check(DrawnTargetLockWidget);
		DrawnTargetLockWidget->AddToViewport();
	}
}

void UGoddessGA_TargetLock::SetTargetLockWidgetPosition()
{
	if (!DrawnTargetLockWidget || !CurrentLockedActor)
	{
		CancelTargetLockAbility();
		return;
	}

	FVector2D ScreenPosition;
	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(
		GetGoddessControllerFromActorInfo(),
		CurrentLockedActor->GetActorLocation(),
		ScreenPosition,
		true
	);

	if (TargetLockWidgetSize == FVector2D::ZeroVector)
	{
		DrawnTargetLockWidget->WidgetTree->ForEachWidget(
			[this](UWidget* FoundWidget)
			{
				if (USizeBox* FoundSizeBox = Cast<USizeBox>(FoundWidget))
				{
					TargetLockWidgetSize.X = FoundSizeBox->GetWidthOverride();
					TargetLockWidgetSize.Y = FoundSizeBox->GetHeightOverride();
				}
			}
		);
	}

	ScreenPosition -= TargetLockWidgetSize / 2.f;
	DrawnTargetLockWidget->SetPositionInViewport(ScreenPosition, false);
}

void UGoddessGA_TargetLock::InitTargetLockMovement()
{
	CachedDefaultMaxWalkSpeed = GetGoddessFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed;

	GetGoddessFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = TargetLockWalkSpeed;
}

void UGoddessGA_TargetLock::CancelTargetLockAbility()
{
	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
}

void UGoddessGA_TargetLock::CleanUp()
{
	AvailableActorsToLock.Empty();

	CurrentLockedActor = nullptr;

	if (DrawnTargetLockWidget)
		DrawnTargetLockWidget->RemoveFromParent();

	DrawnTargetLockWidget = nullptr;

	TargetLockWidgetSize = FVector2D::ZeroVector;

	CachedDefaultMaxWalkSpeed = 0.f;
}

void UGoddessGA_TargetLock::ResetTargetLockMovement()
{
	if (CachedDefaultMaxWalkSpeed > 0.f)
		GetGoddessFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = CachedDefaultMaxWalkSpeed;
}
