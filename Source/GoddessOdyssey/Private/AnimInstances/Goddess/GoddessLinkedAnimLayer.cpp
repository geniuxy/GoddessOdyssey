// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Goddess/GoddessLinkedAnimLayer.h"

#include "AnimInstances/Goddess/GoddessAnimInstance.h"

UGoddessAnimInstance* UGoddessLinkedAnimLayer::GetGoddessAnimInstance() const
{
	return Cast<UGoddessAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
