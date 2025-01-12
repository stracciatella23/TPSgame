// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerComponent/PlayerWeapon.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Items/Weapons/Rifle/Rifle.h"
#include "Items/Weapons/Sniper/Sniper.h"

void UPlayerWeapon::SetupInputBinding(UEnhancedInputComponent* PlayerInput)
{
	// 총 발사
	PlayerInput->BindAction(ia_Fire, ETriggerEvent::Started, this, &UPlayerWeapon::InputFire);
	PlayerInput->BindAction(ia_Fire, ETriggerEvent::Completed, this, &UPlayerWeapon::StopFire);

	// 총 바꾸기
	PlayerInput->BindAction(ia_Changeto0, ETriggerEvent::Started, this, &UPlayerWeapon::Changeto0);
	PlayerInput->BindAction(ia_Changeto1, ETriggerEvent::Started, this, &UPlayerWeapon::Changeto1);

	// 무기 버리기
	PlayerInput->BindAction(ia_Drop, ETriggerEvent::Started, this, &UPlayerWeapon::DropCurrentWeapon);

	// 총 단발/연사 모드 바꾸기
	PlayerInput->BindAction(ia_ChangeGunMode, ETriggerEvent::Started, this, &UPlayerWeapon::ChangeGunMode);

	// 총 스나이퍼 모드
	PlayerInput->BindAction(ia_SniperMode, ETriggerEvent::Started, this, &UPlayerWeapon::SniperMode);
	PlayerInput->BindAction(ia_SniperMode, ETriggerEvent::Completed, this, &UPlayerWeapon::SniperMode);
}

void UPlayerWeapon::InputFire(const FInputActionValue& inptValue)
{
	if (me->WeaponSlots[me->CurrentWeaponSlot])
	{
		// currentWeapon이 Rifle 클래스인지 확인
		ARifle* Rifle = Cast<ARifle>(me->WeaponSlots[me->CurrentWeaponSlot]);
		if (Rifle)
		{
			// Rifle이면 ToggleMode 함수 호출
			Rifle->StartFire();
		}
		else
		{
			// Rifle이 아니면 다른 처리 (선택 사항)
			me->WeaponSlots[me->CurrentWeaponSlot]->Fire();
		}
	}
}

void UPlayerWeapon::StopFire()
{
	if (me->WeaponSlots[me->CurrentWeaponSlot])
	{
		// currentWeapon이 Rifle 클래스인지 확인
		ARifle* Rifle = Cast<ARifle>(me->WeaponSlots[me->CurrentWeaponSlot]);
		if (Rifle)
		{
			// Rifle이면 ToggleMode 함수 호출
			Rifle->StopFire();
		}
	}
}

void UPlayerWeapon::Changeto0()
{
	UE_LOG(LogTemp, Warning, TEXT("changeto0"));
	if (me->CurrentWeaponSlot == 1)
	{
		if (me->WeaponSlots[1])
		{
			me->WeaponSlots[1]->bodyMeshComp->SetVisibility(false);
		}
		if (me->WeaponSlots[0])
		{
			me->WeaponSlots[0]->bodyMeshComp->SetVisibility(true);
		}
		me->CurrentWeaponSlot = 0;
		if (me->WeaponSlots[0])
		{
			me->CurrentWeaponAmmo = me->WeaponSlots[0]->TotalAmmo;
		}
		else
		{
			me->CurrentWeaponAmmo = 0;
		}
	}
}

void UPlayerWeapon::Changeto1()
{
	UE_LOG(LogTemp, Warning, TEXT("changeto1"));
	if (me->CurrentWeaponSlot == 0)
	{
		if (me->WeaponSlots[0])
		{
			me->WeaponSlots[0]->bodyMeshComp->SetVisibility(false);
		}
		if (me->WeaponSlots[1])
		{
			me->WeaponSlots[1]->bodyMeshComp->SetVisibility(true);
		}
		me->CurrentWeaponSlot = 1;
		if (me->WeaponSlots[1])
		{
			me->CurrentWeaponAmmo = me->WeaponSlots[1]->TotalAmmo;
		}
		else
		{
			me->CurrentWeaponAmmo = 0;
		}
	}
}

void UPlayerWeapon::DropCurrentWeapon()
{
	if (me->CurrentWeaponSlot != -1 && me->WeaponSlots[me->CurrentWeaponSlot])
	{
		AWeaponBase* WeaponToDrop = me->WeaponSlots[me->CurrentWeaponSlot];
		me->WeaponSlots[me->CurrentWeaponSlot] = nullptr;
		me->CurrentWeaponAmmo = 0;

		FVector Start = me->GetActorLocation() + me->GetActorForwardVector() * 100.0f;
		FVector End = Start - FVector(0, 0, 500.0f);  // 아래 방향으로 500 유닛 트레이스

		FHitResult HitResult;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(me);

		WeaponToDrop->bodyMeshComp->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

		if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params))
		{
			// 바닥 위치에 무기 배치
			WeaponToDrop->SetActorLocation(HitResult.Location);
			WeaponToDrop->SetActorRotation(FRotator(0, me->GetActorRotation().Yaw, 0));  // 무기의 Yaw 회전만 캐릭터와 맞춤
		}
		else
		{
			// 바닥이 감지되지 않은 경우 기본 위치 설정
			FVector DropLocation = me->GetActorLocation() + me->GetActorForwardVector() * 100.0f;
			WeaponToDrop->SetActorLocation(DropLocation);
		}

		// 무기를 월드에서 보이게 설정하고 충돌 활성화
		//WeaponToDrop->SetActorHiddenInGame(false);
		WeaponToDrop->SetActorEnableCollision(true);

		// 현재 장착 중인 무기 초기화
		//CurrentWeapon = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("Dropped weapon from Slot %d"), me->CurrentWeaponSlot + 1);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No weapon equipped to drop"));
	}
}

void UPlayerWeapon::ChangeGunMode()
{
	if (me->WeaponSlots[me->CurrentWeaponSlot])
	{
		// currentWeapon이 Rifle 클래스인지 확인
		ARifle* Rifle = Cast<ARifle>(me->WeaponSlots[me->CurrentWeaponSlot]);
		if (Rifle)
		{
			// Rifle이면 ToggleMode 함수 호출
			Rifle->ToggleFireMode();
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("ChangeMode is not provided"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("NO gun to change mode!"));
	}
}

void UPlayerWeapon::SniperMode()
{
	if (me->WeaponSlots[me->CurrentWeaponSlot])
	{
		// currentWeapon이 Sniper 클래스인지 확인
		ASniper* Sniper = Cast<ASniper>(me->WeaponSlots[me->CurrentWeaponSlot]);
		if (Sniper)
		{
			// Sniper이면 조준경 확대
			Sniper->SniperMode();
		}
	}
}
