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

	// 발사 간격 (초 단위)
	float FireRate;

	// 연사 모드일 때의 발사 타이머
	FTimerHandle FireTimer;
	
};
