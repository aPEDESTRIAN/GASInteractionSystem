// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GASCharacterMovementComponent.generated.h"


UCLASS()
class GASINTERACTIONSYSTEM_API UGASCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UGASCharacterMovementComponent();

	virtual float GetMaxSpeed() const override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class AGASInteractionSystemCharacter* PrivateOwningCharacter;

	class AGASInteractionSystemCharacter* OwningCharacter();
};
