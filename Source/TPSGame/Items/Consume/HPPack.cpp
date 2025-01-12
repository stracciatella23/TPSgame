// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Consume/HPPack.h"
#include <Components/BoxComponent.h>
#include <Components/SphereComponent.h>

// Sets default values
AHPPack::AHPPack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Recovery = 3;

	// 감지 컴포넌트 추가
	DetectionComponent = CreateDefaultSubobject<UPlayerDetectionComponent>(TEXT("DetectionComponent"));

	bodyMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BodyMeshComp"));
	bodyMeshComp->SetupAttachment(collisionComp);
	RootComponent = bodyMeshComp;


	collisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	collisionComp->SetCollisionProfileName(TEXT("BlockAll"));
	collisionComp->SetupAttachment(bodyMeshComp);

	if (bodyMeshComp->SkeletalMesh)
	{
		FVector MeshBounds = bodyMeshComp->Bounds.BoxExtent;
		collisionComp->SetBoxExtent(MeshBounds);
	}

	DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
	DetectionSphere->InitSphereRadius(200.f);  // 감지 범위 반경 설정
	DetectionSphere->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AHPPack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHPPack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHPPack::Interact_Implementation(AMyCharacter* Character)
{
	Character->HP += Recovery;

	if (Character->HP > Character->initialHP)
	{
		Character->HP = Character->initialHP;
	}

	Destroy();
}