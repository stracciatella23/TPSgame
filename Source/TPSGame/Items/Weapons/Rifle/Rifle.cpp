// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/Rifle/Rifle.h"

ARifle::ARifle()
{
	// 기본 발사 모드: 단발
	bIsAutomaticFire = false;

	// 발사 간격 설정 (예: 0.1초마다 발사)
	FireRate = 0.1f;
}

void ARifle::StartFire()
{

	if (bIsAutomaticFire)
	{
		// 연사 모드 - 일정 간격으로 발사
		GetWorld()->GetTimerManager().SetTimer(FireTimer, this, &AWeaponBase::Fire, FireRate, true);
	}
	else
	{
		// 단발 모드 - 한 번만 발사
		Fire();
	}

}

void ARifle::StopFire()
{
	// 연사 모드일 경우 타이머 정지
	if (bIsAutomaticFire)
	{
		UE_LOG(LogTemp, Log, TEXT("StopFIre"));
		GetWorld()->GetTimerManager().ClearTimer(FireTimer);
	}
}

void ARifle::ToggleFireMode()
{
	/*
	if (bIsAutomaticFirePossible == false)
	{
		UE_LOG(LogTemp, Log, TEXT("no mode change provided"));
		//return;
	}
	else
	{
		bIsAutomaticFire = !bIsAutomaticFire;
		if (bIsAutomaticFire)
		{
			UE_LOG(LogTemp, Log, TEXT("change to continues shot mode"));
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("change to single shot mode"));
		}
	}
	*/
	bIsAutomaticFire = !bIsAutomaticFire;
	if (bIsAutomaticFire)
	{
		UE_LOG(LogTemp, Log, TEXT("change to continues shot mode"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("change to single shot mode"));
	}
}