// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerComponent/PlayerMove.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

UPlayerMove::UPlayerMove()
{
	// Tick 함수 호출되도록 처리
	PrimaryComponentTick.bCanEverTick = false;

}

void UPlayerMove::BeginPlay()
{
	Super::BeginPlay();

	// 초기 속도를 걷기로 설정
	moveComp->MaxWalkSpeed = walkSpeed;
}

void UPlayerMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerMove::SetupInputBinding(UEnhancedInputComponent* PlayerInput)
{
	// 이동
	PlayerInput->BindAction(ia_Move, ETriggerEvent::Triggered, this, &UPlayerMove::Move);
	// 달리기
	PlayerInput->BindAction(ia_PlayerRun, ETriggerEvent::Started, this, &UPlayerMove::Run);
	PlayerInput->BindAction(ia_PlayerRun, ETriggerEvent::Completed, this, &UPlayerMove::Run);
	// 점프
	PlayerInput->BindAction(ia_PlayerJump, ETriggerEvent::Started, this, &UPlayerMove::InputJump);
}

void UPlayerMove::Move(const FInputActionValue& inputValue)
{
	FVector2D value = inputValue.Get<FVector2D>();

	me->direction.X = value.X;
	me->direction.Y = value.Y;
}

void UPlayerMove::Run()
{
	if (bIsRunning)
	{
		bIsRunning = false;
		me->GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
	}
	else
	{
		bIsRunning = true;
		me->GetCharacterMovement()->MaxWalkSpeed = runSpeed;
	}
}

void UPlayerMove::InputJump(const FInputActionValue& inputValue)
{
	me->Jump();
}
