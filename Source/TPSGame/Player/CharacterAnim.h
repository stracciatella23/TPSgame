// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnim.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAME_API UCharacterAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	// �÷��̾� �յ� �̵� �ӵ�
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
	float speed = 0;

	// �÷��̾� �¿� �̵� �ӵ�
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
	float direction = 0;

	// �� ������ ���ŵǴ� �Լ�
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	// �÷��̾� ���� ��
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
	bool isInAir = 0;

	// ����� ���� �ִϸ��̼� ��Ÿ��
	UPROPERTY(EditDefaultsOnly, Category = PlayerAnim)
	class UAnimMontage* attackAnimMontage;
	// ���� �ִϸ��̼� ��� �Լ�
	void PlayAttackAnim();
};
