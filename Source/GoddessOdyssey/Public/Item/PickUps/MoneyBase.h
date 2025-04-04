// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUpBase.h"
#include "GameFramework/Actor.h"
#include "MoneyBase.generated.h"

class UGameplayEffect;
class UBaseAbilitySystemComponent;

UCLASS()
class GODDESSODYSSEY_API AMoneyBase : public APickUpBase
{
	GENERATED_BODY()
	
public:	
	UFUNCTION(BlueprintCallable)
	void Consume(UBaseAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data Table|Money")
	FDataTableRowHandle MoneyHandle;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> MoneyGameplayEffectClass;

	virtual void OnPickUpCollisionSphereBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	) override;
};
