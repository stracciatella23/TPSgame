// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Consume/Ammo.h"
#include <Components/BoxComponent.h>
#include <Components/SphereComponent.h>

// Sets default values
AAmmo::AAmmo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Ammocnt = 10;

	// 감지 컴포넌트 추가
	DetectionComponent = CreateDefaultSubobject<UPlayerDetectionComponent>(TEXT("DetectionComponent"));

	//bodyMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BodyMeshComp"));
	bodyMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMeshComp"));
	bodyMeshComp->SetupAttachment(collisionComp);
	RootComponent = bodyMeshComp;


	collisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	collisionComp->SetCollisionProfileName(TEXT("BlockAll"));
	collisionComp->SetupAttachment(bodyMeshComp);

	/*
	if (bodyMeshComp->SkeletalMesh)
	{
		FVector MeshBounds = bodyMeshComp->Bounds.BoxExtent;
		collisionComp->SetBoxExtent(MeshBounds);
	}
	*/
	DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
	DetectionSphere->InitSphereRadius(200.f);  // 감지 범위 반경 설정
	DetectionSphere->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AAmmo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAmmo::Interact_Implementation(AMyCharacter* Character)
{
	if (Character->WeaponSlots[Character->CurrentWeaponSlot])
	{
		Character->CurrentWeaponAmmo += Ammocnt;

		Destroy();
	}
}