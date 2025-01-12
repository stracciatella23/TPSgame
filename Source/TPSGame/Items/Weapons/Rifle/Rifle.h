// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/WeaponBase.h"
#include "Rifle.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAME_API ARifle : public AWeaponBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARifle();

public:

	UFUNCTION(BlueprintCallable)
	void StartFire();

	UFUNCTION(BlueprintCallable)
	void StopFire();

	UFUNCTION(BlueprintCallable)
	void ToggleFireMode();

	bool bIsAutomaticFire;

	// �߻� ���� (�� ����)
	float FireRate;

	// ���� ����� ���� �߻� Ÿ�̸�
	FTimerHandle FireTimer;
	
};
