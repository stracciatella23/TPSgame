// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerComponent/PlayerBaseComponent.h"
#include "PlayerCamera.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAME_API UPlayerCamera : public UPlayerBaseComponent
{
	GENERATED_BODY()
	
public: 
	virtual void SetupInputBinding(class UEnhancedInputComponent* PlayerInput) override;

	// ���콺 ����
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_LookUp;
	void LookUp(const struct FInputActionValue& inputValue);

	// ���콺 �¿�
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_Turn;
	void Turn(const struct FInputActionValue& inputValue);
};
