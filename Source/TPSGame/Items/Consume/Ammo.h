// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Items/BaseInteractive.h"
#include "Items/PlayerDetectionComponent.h"
#include "Ammo.generated.h"

UCLASS()
class TPSGAME_API AAmmo : public AActor, public IBaseInteractive
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmo();

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

	UFUNCTION(BlueprintCallable, Category = "Ammo")
	virtual void Interact_Implementation(AMyCharacter* Character) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 Ammocnt;
};
