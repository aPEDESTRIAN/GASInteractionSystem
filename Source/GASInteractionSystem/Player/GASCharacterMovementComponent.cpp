// Fill out your copyright notice in the Description page of Project Settings.

#include "GASInteractionSystem/Player/GASCharacterMovementComponent.h"
#include "GASInteractionSystem/Player/GASInteractionSystemCharacter.h"


UGASCharacterMovementComponent::UGASCharacterMovementComponent()
	: PrivateOwningCharacter(nullptr)
{
	//...
}

float UGASCharacterMovementComponent::GetMaxSpeed() const
{
	if (PrivateOwningCharacter == nullptr)
	{
		return Super::GetMaxSpeed();
	}
	else
	{
		return Super::GetMaxSpeed() * PrivateOwningCharacter->GetSpeed();
	}
}

void UGASCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	PrivateOwningCharacter = CastChecked<AGASInteractionSystemCharacter>(GetOwner(), ECastCheckedType::NullChecked);
}

AGASInteractionSystemCharacter* UGASCharacterMovementComponent::OwningCharacter()
{
	if (PrivateOwningCharacter == nullptr)
	{
		PrivateOwningCharacter = CastChecked<AGASInteractionSystemCharacter>(GetOwner(), ECastCheckedType::NullChecked);
	}

	return PrivateOwningCharacter;
}