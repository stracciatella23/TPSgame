// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerComponent/PlayerCamera.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

void UPlayerCamera::Turn(const FInputActionValue& inputValue)
{
	float value = inputValue.Get<float>();
	me->AddControllerYawInput(value);
}

void UPlayerCamera::LookUp(const FInputActionValue& inputValue)
{
	float value = inputValue.Get<float>();
	me->AddControllerPitchInput(value);
}

void UPlayerCamera::SetupInputBinding(UEnhancedInputComponent* PlayerInput)
{
	// Ä«¸Þ¶ó
	PlayerInput->BindAction(ia_Turn, ETriggerEvent::Triggered, this, &UPlayerCamera::Turn);
	PlayerInput->BindAction(ia_LookUp, ETriggerEvent::Triggered, this, &UPlayerCamera::LookUp);
}