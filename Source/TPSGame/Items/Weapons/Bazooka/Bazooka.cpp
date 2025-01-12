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
	// Channel 필터를 이용한 LineTrace 충돌 검출(충돌 정보, 시작 위치, 종료 위치, 검출 채널, 충돌 옵션)
	bool bHit = GetWorld()->LineTraceSingleByChannel(hitInfo, startPos, endPos, ECC_Visibility, params);
	// LineTrace가 부딪혔을 때
	if (bHit)
	{
		//auto hitComp = hitInfo.GetComponent();
		endPos = hitInfo.ImpactPoint;
		UE_LOG(LogTemp, Log, TEXT("Bazooka bHit!!"));
	}


	// 카메라 방향 가져오기
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
