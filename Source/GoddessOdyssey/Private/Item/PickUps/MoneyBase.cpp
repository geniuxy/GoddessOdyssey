// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PickUps/MoneyBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "DebugHelper.h"
#include "GameplayEffect.h"
#include "GoddessGameplayTags.h"
#include "AbilitySystems/BaseAbilitySystemComponent.h"
#include "Characters/Goddess.h"

AMoneyBase::AMoneyBase()
{
	MoneyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Money"));
	MoneyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MoneyMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	MoneyMesh->SetupAttachment(GetRootComponent());
}

void AMoneyBase::Consume(UBaseAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel)
{
	check(MoneyGameplayEffectClass);

	UGameplayEffect* MoneyGameplayEffect = MoneyGameplayEffectClass->GetDefaultObject<UGameplayEffect>();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->ApplyGameplayEffectToSelf(
			MoneyGameplayEffect,
			ApplyLevel,
			AbilitySystemComponent->MakeEffectContext()
		);
	}

	Destroy();

	// BP_OnMoneyConsumed();
}

void AMoneyBase::OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                                     bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnPickUpCollisionSphereBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep,
	                                           SweepResult);

	if (AGoddess* Goddess = Cast<AGoddess>(OtherActor))
	{
		// Debug::Print(TEXT("I Found Money"));
		
		FGameplayEventData Data;
		Data.Instigator = this;
		Data.Target = Goddess;
		
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			Goddess,
			GoddessGameplayTags::Character_Event_ConsumeMoney,
			Data
		);
	}
}
