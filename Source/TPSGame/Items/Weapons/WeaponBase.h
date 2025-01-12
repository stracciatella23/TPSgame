// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Items/BaseInteractive.h"
#include "Items/PlayerDetectionComponent.h"
#include "WeaponBase.generated.h"

UCLASS()
class TPSGAME_API AWeaponBase : public AActor, public IBaseInteractive
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Collision ������Ʈ
	UPROPERTY(VisibleAnywhere, Category = Collision)
	class UBoxComponent* collisionComp;

	// �ܰ� ������Ʈ
	UPROPERTY(VisibleAnywhere, Category = BodyMesh)
	//class USkeletalMeshComponent* bodyMeshComp;
	class UStaticMeshComponent* bodyMeshComp;

	// ������ ���� ������Ʈ
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* DetectionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPlayerDetectionComponent* DetectionComponent;

	//virtual void Interact(AMyCharacter* Character) override;
	virtual void Interact_Implementation(AMyCharacter* Character) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 TotalAmmo = 30;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 LoadedAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 MaxAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 Damage;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	//bool bIsAutomaticFirePossible = false;

	// �߻� ���
	/*
	UFUNCTION(BlueprintCallable)
	void StartFire();

	UFUNCTION(BlueprintCallable)
	void StopFire();

	UFUNCTION(BlueprintCallable)
	void ToggleFireMode();
	*/

	virtual void Fire();

	/*
	// �ܹ�/���� ��� ����
	bool bIsAutomaticFire;

	// �߻� ���� (�� ����)
	float FireRate;

	// ���� ����� ���� �߻� Ÿ�̸�
	FTimerHandle FireTimer;
	*/

	class AMyCharacter* tmpCharacter;

	// �Ѿ� ���� ȿ��
	UPROPERTY(EditAnywhere, Category = BulletEffect)
	class UParticleSystem* bulletEffectFactory;

};
