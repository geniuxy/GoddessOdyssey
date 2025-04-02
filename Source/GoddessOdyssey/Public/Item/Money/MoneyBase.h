// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoneyBase.generated.h"

UCLASS()
class GODDESSODYSSEY_API AMoneyBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AMoneyBase();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* MoneyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data Table")
	FDataTableRowHandle MoneyHandle;
};
