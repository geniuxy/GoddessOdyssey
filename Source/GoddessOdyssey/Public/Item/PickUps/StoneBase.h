// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUpBase.h"
#include "StoneBase.generated.h"

class UGameplayEffect;
class UBaseAbilitySystemComponent;

UCLASS()
class GODDESSODYSSEY_API AStoneBase : public APickUpBase
{
	GENERATED_BODY()

public:
	void Consume(UBaseAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel);

protected:
	virtual void OnPickUpCollisionSphereBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	) override;

	UFUNCTION(BlueprintImplementableEvent,meta=(DisplayName="On Stone Consumed"))
	void BP_OnStoneConsumed();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> StoneGameplayEffectClass;
};
