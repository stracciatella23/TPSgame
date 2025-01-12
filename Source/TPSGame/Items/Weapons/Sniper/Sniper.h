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


	// �������� UI ����
	UPROPERTY(EditDefaultsOnly, Category = SniperUI)
	TSubclassOf<class UUserWidget> sniperUIFactory;

	// �������� UI ���� �ν��Ͻ�
	UPROPERTY()
	class UUserWidget* sniperUI;
};
