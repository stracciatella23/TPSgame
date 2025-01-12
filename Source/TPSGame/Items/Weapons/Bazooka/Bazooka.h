// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/WeaponBase.h"
#include "Bazooka.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAME_API ABazooka : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	virtual void Fire() override;

	UPROPERTY(EditDefaultsOnly, Category = BulletFactory)
	TSubclassOf<class ABullet> bulletFactory;
};
