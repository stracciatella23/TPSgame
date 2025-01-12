// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerComponent/PlayerBaseComponent.h"
#include "PlayerMove.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAME_API UPlayerMove : public UPlayerBaseComponent
{
	GENERATED_BODY()
	
public:

	UPlayerMove();

	virtual void SetupInputBinding(class UEnhancedInputComponent* PlayerInput) override;
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// 이동
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_Move;
	void Move(const struct FInputActionValue& inputValue);

	// 걷기 속도
	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float walkSpeed = 200;
	// 뛰기 속도
	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float runSpeed = 600;

	// 달리기
	UPROPERTY(EditDefaultsOnly, category = "Input")
	class UInputAction* ia_PlayerRun;
	void Run();
	bool bIsRunning; // 달리기 여부

	// 점프
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_PlayerJump;
	void InputJump(const struct FInputActionValue& inputValue);
};
