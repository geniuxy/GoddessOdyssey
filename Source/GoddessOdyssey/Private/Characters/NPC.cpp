// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPC.h"

#include "GoddessGameplayTags.h"
#include "AbilitySystems/BaseAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Characters/Goddess.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/SpringArmComponent.h"


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

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
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
