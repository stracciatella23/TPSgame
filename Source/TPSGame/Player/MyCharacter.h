// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class TPSGAME_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* springArmComp;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* tpsCamComp; // 3��Ī ī�޶�

public:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* imc_MyProject;

	// ������Ʈ�� ��ȣ�ۿ�
	UPROPERTY(EditDefaultsOnly, category = "Input")
	class UInputAction* ia_Interact;
	void Interact();

	// ��ȣ�ۿ� ����
	UPROPERTY(EditDefaultsOnly, Category = DetectionDistance)
	int LineTraceDetectionDistance = 2000;

	// �̵� ó��
	void Move();
	FVector direction;

	// 2���� ���� ����
	class AWeaponBase* WeaponSlots[2] = { nullptr, nullptr };
	// ���� ���� ���� ���� ���� �ε��� (0 �Ǵ� 1)
	int32 CurrentWeaponSlot = 0;

	// �ڵ��� ž�� ����
	bool inCar = false;

public:
	// ũ�ν� ��� 
	UPROPERTY(EditDefaultsOnly, Category = CrosshairUI)
	TSubclassOf<class UUserWidget> crosshairUIFactory;
	UPROPERTY()
	class UUserWidget* crosshairUI;

public:
	
	UPROPERTY(VisibleAnywhere, Category = Component)
	class UPlayerBaseComponent* playerMove;
	
	UPROPERTY(VisibleAnywhere, Category = Component)
	class UPlayerBaseComponent* playerWeapon;
	
	UPROPERTY(VisibleAnywhere, Category = Component)
	class UPlayerBaseComponent* playerCamera;
	

	// ���� HP
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = HP)
	int32 HP;
	// ���� HP
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = HP)
	int32 initialHP = 10;

	// �ǰݽ� �Լ�
	UFUNCTION(BlueprintCallable, Category = HP)
	void OnHitEvent();

	// ���ӿ��� �Լ�
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Health)
	void OnGameOver();

	// �� ų ��
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Kill)
	int32 TotalKill = 0;

	// �¸����� �Լ�
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Health)
	void YouWin();

	// ���� ���� ź�� ��
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Ammo)
	int32 CurrentWeaponAmmo = 0;

};
