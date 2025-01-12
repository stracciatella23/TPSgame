// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/WeaponBase.h"
#include "Sniper.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAME_API ASniper : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	ASniper();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	void SniperMode();

	bool bIsSniperMode;


	// 스나이퍼 UI 위젯
	UPROPERTY(EditDefaultsOnly, Category = SniperUI)
	TSubclassOf<class UUserWidget> sniperUIFactory;

	// 스나이퍼 UI 위젯 인스턴스
	UPROPERTY()
	class UUserWidget* sniperUI;
};
