// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Player/MyCharacter.h"
#include "BaseInteractive.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBaseInteractive : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TPSGAME_API IBaseInteractive
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	//virtual void Interact(AMyCharacter* Character) = 0;
	void Interact(AMyCharacter* Character);
	//void Interact(class AMyCharacter* Character);
};
