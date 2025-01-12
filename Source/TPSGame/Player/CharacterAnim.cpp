// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CharacterAnim.h"
#include "Player/MyCharacter.h"
#include <GameFramework/CharacterMovementComponent.h>

void UCharacterAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// 플레이어의 이동 속도를 speed에 할당
	auto ownerPawn = TryGetPawnOwner();
	auto player = Cast<AMyCharacter>(ownerPawn);

	if (player)
	{
		FVector velocity = player->GetVelocity();
		FVector forwardVector = player->GetActorForwardVector();
		// 내적 후 값에 따라 앞으로 가는지 뒤로 가는지 판별
		speed = FVector::DotProduct(forwardVector, velocity);

		FVector rightVector = player->GetActorRightVector();
		// 내적 후 값에 따라 오른쪽으로 가는지 왼쪽으로 가는지 판별
		direction = FVector::DotProduct(rightVector, velocity);

		// 플레이어가 공중에 있는지 여부 판별
		auto movement = player->GetCharacterMovement();
		isInAir = movement->IsFalling();
	}
}

void UCharacterAnim::PlayAttackAnim()
{
	Montage_Play(attackAnimMontage);
}