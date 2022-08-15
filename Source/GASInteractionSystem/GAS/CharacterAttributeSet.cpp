// Fill out your copyright notice in the Description page of Project Settings.

#include "GASInteractionSystem/GAS/CharacterAttributeSet.h"
#include "Net/UnrealNetwork.h"


void UCharacterAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Can't use DOREPLIFETIME(UBaseAttributeSet, Health) because of replication errors that occur with attributes and the ability system
	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterAttributeSet, Speed, COND_None, REPNOTIFY_Always);
}