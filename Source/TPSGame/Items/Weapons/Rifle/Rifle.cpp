// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/Rifle/Rifle.h"

ARifle::ARifle()
{
	// �⺻ �߻� ���: �ܹ�
	bIsAutomaticFire = false;

	// �߻� ���� ���� (��: 0.1�ʸ��� �߻�)
	FireRate = 0.1f;
}

void ARifle::StartFire()
{

	if (bIsAutomaticFire)
	{
		// ���� ��� - ���� �������� �߻�
		GetWorld()->GetTimerManager().SetTimer(FireTimer, this, &AWeaponBase::Fire, FireRate, true);
	}
	else
	{
		// �ܹ� ��� - �� ���� �߻�
		Fire();
	}

}

void ARifle::StopFire()
{
	// ���� ����� ��� Ÿ�̸� ����
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