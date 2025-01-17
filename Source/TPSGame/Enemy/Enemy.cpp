// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Enemy.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 1. 스켈레탈메시 데이터 로드
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequin_UE4/Meshes/SK_Mannequin.SK_Mannequin'"));
	// 1-1. 데이터 로드 성공하면
	if (tempMesh.Succeeded())
	{
		// 1-2. 데이터 할당
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		// 1-3. 메시 위치 및 회전 설정
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -88), FRotator(0, -90, 0));

		GetMesh()->SetRelativeScale3D(FVector(0.82f));
	}

	/*
	// EnemyFSM 컴포넌트 추가
	fsm = CreateDefaultSubobject<UEnemyFSM>(TEXT("FSM"));

	// 애니메이션 블루프린트 할당하기
	ConstructorHelpers::FClassFinder<UAnimInstance> tempClass(TEXT("/Script/Engine.AnimBlueprint'/Game/Blueprints/ABP_Enemy.ABP_Enemy_C'"));
	if (tempClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(tempClass.Class);
	}

	// 월드에 배치되거나 스폰될 때 자동으로 
	// AIController부터 Possess될 수 있도록 설정
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	*/
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

