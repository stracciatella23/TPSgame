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

	// Collision 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = Collision)
	class UBoxComponent* collisionComp;

	// 외관 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = BodyMesh)
	//class USkeletalMeshComponent* bodyMeshComp;
	class UStaticMeshComponent* bodyMeshComp;

	// 감지를 위한 컴포넌트
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

	// 발사 기능
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
	// 단발/연사 모드 설정
	bool bIsAutomaticFire;

	// 발사 간격 (초 단위)
	float FireRate;

	// 연사 모드일 때의 발사 타이머
	FTimerHandle FireTimer;
	*/

	class AMyCharacter* tmpCharacter;

	// 총알 파편 효과
	UPROPERTY(EditAnywhere, Category = BulletEffect)
	class UParticleSystem* bulletEffectFactory;

};
