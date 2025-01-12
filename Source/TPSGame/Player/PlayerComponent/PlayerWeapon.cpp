// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerComponent/PlayerWeapon.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Items/Weapons/Rifle/Rifle.h"
#include "Items/Weapons/Sniper/Sniper.h"

void UPlayerWeapon::SetupInputBinding(UEnhancedInputComponent* PlayerInput)
{
	// �� �߻�
	PlayerInput->BindAction(ia_Fire, ETriggerEvent::Started, this, &UPlayerWeapon::InputFire);
	PlayerInput->BindAction(ia_Fire, ETriggerEvent::Completed, this, &UPlayerWeapon::StopFire);

	// �� �ٲٱ�
	PlayerInput->BindAction(ia_Changeto0, ETriggerEvent::Started, this, &UPlayerWeapon::Changeto0);
	PlayerInput->BindAction(ia_Changeto1, ETriggerEvent::Started, this, &UPlayerWeapon::Changeto1);

	// ���� ������
	PlayerInput->BindAction(ia_Drop, ETriggerEvent::Started, this, &UPlayerWeapon::DropCurrentWeapon);

	// �� �ܹ�/���� ��� �ٲٱ�
	PlayerInput->BindAction(ia_ChangeGunMode, ETriggerEvent::Started, this, &UPlayerWeapon::ChangeGunMode);

	// �� �������� ���
	PlayerInput->BindAction(ia_SniperMode, ETriggerEvent::Started, this, &UPlayerWeapon::SniperMode);
	PlayerInput->BindAction(ia_SniperMode, ETriggerEvent::Completed, this, &UPlayerWeapon::SniperMode);
}

void UPlayerWeapon::InputFire(const FInputActionValue& inptValue)
{
	if (me->WeaponSlots[me->CurrentWeaponSlot])
	{
		// currentWeapon�� Rifle Ŭ�������� Ȯ��
		ARifle* Rifle = Cast<ARifle>(me->WeaponSlots[me->CurrentWeaponSlot]);
		if (Rifle)
		{
			// Rifle�̸� ToggleMode �Լ� ȣ��
			Rifle->StartFire();
		}
		else
		{
			// Rifle�� �ƴϸ� �ٸ� ó�� (���� ����)
			me->WeaponSlots[me->CurrentWeaponSlot]->Fire();
		}
	}
}

void UPlayerWeapon::StopFire()
{
	if (me->WeaponSlots[me->CurrentWeaponSlot])
	{
		// currentWeapon�� Rifle Ŭ�������� Ȯ��
		ARifle* Rifle = Cast<ARifle>(me->WeaponSlots[me->CurrentWeaponSlot]);
		if (Rifle)
		{
			// Rifle�̸� ToggleMode �Լ� ȣ��
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
		FVector End = Start - FVector(0, 0, 500.0f);  // �Ʒ� �������� 500 ���� Ʈ���̽�

		FHitResult HitResult;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(me);

		WeaponToDrop->bodyMeshComp->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

		if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params))
		{
			// �ٴ� ��ġ�� ���� ��ġ
			WeaponToDrop->SetActorLocation(HitResult.Location);
			WeaponToDrop->SetActorRotation(FRotator(0, me->GetActorRotation().Yaw, 0));  // ������ Yaw ȸ���� ĳ���Ϳ� ����
		}
		else
		{
			// �ٴ��� �������� ���� ��� �⺻ ��ġ ����
			FVector DropLocation = me->GetActorLocation() + me->GetActorForwardVector() * 100.0f;
			WeaponToDrop->SetActorLocation(DropLocation);
		}

		// ���⸦ ���忡�� ���̰� �����ϰ� �浹 Ȱ��ȭ
		//WeaponToDrop->SetActorHiddenInGame(false);
		WeaponToDrop->SetActorEnableCollision(true);

		// ���� ���� ���� ���� �ʱ�ȭ
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
		// currentWeapon�� Rifle Ŭ�������� Ȯ��
		ARifle* Rifle = Cast<ARifle>(me->WeaponSlots[me->CurrentWeaponSlot]);
		if (Rifle)
		{
			// Rifle�̸� ToggleMode �Լ� ȣ��
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
		// currentWeapon�� Sniper Ŭ�������� Ȯ��
		ASniper* Sniper = Cast<ASniper>(me->WeaponSlots[me->CurrentWeaponSlot]);
		if (Sniper)
		{
			// Sniper�̸� ���ذ� Ȯ��
			Sniper->SniperMode();
		}
	}
}
