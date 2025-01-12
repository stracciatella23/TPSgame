// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CharacterAnim.h"
#include "Player/MyCharacter.h"
#include <GameFramework/CharacterMovementComponent.h>

void UCharacterAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// �÷��̾��� �̵� �ӵ��� speed�� �Ҵ�
	auto ownerPawn = TryGetPawnOwner();
	auto player = Cast<AMyCharacter>(ownerPawn);

	if (player)
	{
		FVector velocity = player->GetVelocity();
		FVector forwardVector = player->GetActorForwardVector();
		// ���� �� ���� ���� ������ ������ �ڷ� ������ �Ǻ�
		speed = FVector::DotProduct(forwardVector, velocity);

		FVector rightVector = player->GetActorRightVector();
		// ���� �� ���� ���� ���������� ������ �������� ������ �Ǻ�
		direction = FVector::DotProduct(rightVector, velocity);

		// �÷��̾ ���߿� �ִ��� ���� �Ǻ�
		auto movement = player->GetCharacterMovement();
		isInAir = movement->IsFalling();
	}
}

void UCharacterAnim::PlayAttackAnim()
{
	Montage_Play(attackAnimMontage);
}