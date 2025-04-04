// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class USphereComponent;
class UNiagaraComponent;

UENUM(BlueprintType)
enum class EItemState : uint8
{
	EIS_Hovering UMETA(DisplayName = "Hovering"),
	EIS_Carried UMETA(DisplayName = "Carried"),
	EIS_Equipped UMETA(DisplayName = "Equipped"),
};

UCLASS()
class GODDESSODYSSEY_API AItem : public AActor
{
	GENERATED_BODY()

public:
	AItem();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Sine Parameters")
	float Amplitude = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Sine Parameters")
	float TimeConstant = 10.f;

	UFUNCTION(BlueprintPure)
	float TransformedSin();

	UFUNCTION(BlueprintPure)
	float TransformedCos();

	template <typename T>
	T Avg(T First, T Second);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(BlueprintReadWrite)
	EItemState ItemState = EItemState::EIS_Hovering;

	UPROPERTY(EditAnywhere)
	UNiagaraComponent* EmbersEffect;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	float RunningTime;

public:
};

template <typename T>
T AItem::Avg(T First, T Second)
{
	return (First + Second) / 2;
}

