// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPC.h"

#include "GoddessGameplayTags.h"
#include "AbilitySystems/BaseAbilitySystemComponent.h"
#include "Characters/Goddess.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"


ANPC::ANPC()
{
	TalkCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickUpCollisionSphere"));
	TalkCollisionSphere->SetupAttachment(GetRootComponent());
	TalkCollisionSphere->InitSphereRadius(50.f);
	TalkCollisionSphere->
		OnComponentBeginOverlap.AddUniqueDynamic(this, &ANPC::OnTalkCollisionSphereBeginOverlap);
	TalkCollisionSphere->
		OnComponentEndOverlap.AddUniqueDynamic(this, &ANPC::OnTalkCollisionSphereEndOverlap);

	TalkWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("TalkWidget"));
	TalkWidget->SetupAttachment(RootComponent);
}

void ANPC::BeginPlay()
{
	Super::BeginPlay();

	SetTalkWidgetVisibility(false);
}

void ANPC::SetTalkWidgetVisibility(bool bWasVisible)
{
	if (TalkWidget)
		TalkWidget->SetVisibility(bWasVisible);
}

void ANPC::OnTalkCollisionSphereBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (AGoddess* Goddess = Cast<AGoddess>(OtherActor))
	{
		SetTalkWidgetVisibility(true);
		
		Goddess->GetBaseAbilitySystemComponent()
			   ->TryActivateAbilityByTag(GoddessGameplayTags::Character_Ability_Enter_Shop);
	}
}

void ANPC::OnTalkCollisionSphereEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (AGoddess* Goddess = Cast<AGoddess>(OtherActor))
	{
		SetTalkWidgetVisibility(false);
	}
}
