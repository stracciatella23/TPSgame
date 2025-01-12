// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerComponent/PlayerBaseComponent.h"
#include "PlayerWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAME_API UPlayerWeapon : public UPlayerBaseComponent
{
	GENERATED_BODY()

public:
	virtual void SetupInputBinding(class UEnhancedInputComponent* PlayerInput) override;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* ia_Fire;
	void InputFire(const struct FInputActionValue& inptValue);
	void StopFire();

	UPROPERTY(EditDefaultsOnly, category = "Input")
	class UInputAction* ia_Changeto0;
	void Changeto0();

	UPROPERTY(EditDefaultsOnly, category = "Input")
	class UInputAction* ia_Changeto1;
	void Changeto1();

	// 무기 버리기
	UPROPERTY(EditDefaultsOnly, category = "Input")
	class UInputAction* ia_Drop;
	void DropCurrentWeapon();

	UPROPERTY(EditDefaultsOnly, category = "Input")
	class UInputAction* ia_ChangeGunMode;
	void ChangeGunMode();

	UPROPERTY(EditDefaultsOnly, category = "Input")
	class UInputAction* ia_SniperMode;
	void SniperMode();
	
};
