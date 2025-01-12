// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/Bazooka/Bazooka.h"
#include <Camera/CameraComponent.h>
#include "Items/Weapons/Bazooka/Bullet.h"

void ABazooka::Fire()
{
	UE_LOG(LogTemp, Log, TEXT("Bazooka Fire!!"));

	if (TotalAmmo <= 0) return;

	TotalAmmo--;
	tmpCharacter->CurrentWeaponAmmo--;

	FVector startPos;
	FVector endPos;
	
	startPos = tmpCharacter->tpsCamComp->GetComponentLocation();
	endPos = tmpCharacter->tpsCamComp->GetComponentLocation() + tmpCharacter->tpsCamComp->GetForwardVector() * 5000;

	FHitResult hitInfo;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	// Channel ���͸� �̿��� LineTrace �浹 ����(�浹 ����, ���� ��ġ, ���� ��ġ, ���� ä��, �浹 �ɼ�)
	bool bHit = GetWorld()->LineTraceSingleByChannel(hitInfo, startPos, endPos, ECC_Visibility, params);
	// LineTrace�� �ε����� ��
	if (bHit)
	{
		//auto hitComp = hitInfo.GetComponent();
		endPos = hitInfo.ImpactPoint;
		UE_LOG(LogTemp, Log, TEXT("Bazooka bHit!!"));
	}


	// ī�޶� ���� ��������
	FRotator CameraRotation = tmpCharacter->GetControlRotation();
	FVector ShootDirection = CameraRotation.Vector();
	FTransform firePosition = tmpCharacter->WeaponSlots[tmpCharacter->CurrentWeaponSlot]->bodyMeshComp->GetSocketTransform(TEXT("Muzzle"));
	//FVector firePositionVector = tmpCharacter->WeaponSlots[tmpCharacter->CurrentWeaponSlot]->bodyMeshComp->GetSocketLocation(TEXT("Muzzle"));
	//GetWorld()->SpawnActor<ABullet>(ABullet::StaticClass(), firePosition);
	//FVector ShootDirection = endPos - firePositionVector;
	//UE_LOG(LogTemp, Log, TEXT("Fire Position: %s"), *firePositionVector.ToString());
	//UE_LOG(LogTemp, Log, TEXT("Shoot Direction: %s"), *ShootDirection.ToString());
	ABullet* Bullet = tmpCharacter->GetWorld()->SpawnActor<ABullet>(bulletFactory, firePosition);
	if (Bullet)
	{
		UE_LOG(LogTemp, Log, TEXT("Bazooka Bullet"));
		Bullet->FireInDirection(ShootDirection);
		Bullet->bulletdamage = Damage;
	}


	UE_LOG(LogTemp, Log, TEXT("Bazooka end!!"));
}
