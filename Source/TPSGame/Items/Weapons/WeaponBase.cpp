// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/WeaponBase.h"
#include <Components/SphereComponent.h> // USphereComponent
#include <Components/BoxComponent.h>
#include <Camera/CameraComponent.h>
#include "Components/PrimitiveComponent.h"
#include <Kismet/GameplayStatics.h>
#include "Enemy/EnemyFSM.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// 감지 컴포넌트 추가
	DetectionComponent = CreateDefaultSubobject<UPlayerDetectionComponent>(TEXT("DetectionComponent"));

	// 5. 외관 컴포넌트 등록하기
	//bodyMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BodyMeshComp"));
	bodyMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMeshComp"));
	// 6. 부모 컴포넌트 지정
	bodyMeshComp->SetupAttachment(collisionComp);
	RootComponent = bodyMeshComp;
	// 7. 충돌 비활성화
	//bodyMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//bodyMeshComp->SetCollisionProfileName(TEXT("BloackAll"));
	// 8. 외관 크기 설정
	//bodyMeshComp->SetRelativeScale3D(FVector(0.25f));

	// 1. 충돌체 등록
	collisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	// 2. 충돌 프로파일 설정
	collisionComp->SetCollisionProfileName(TEXT("BlockAll"));
	// 3. 충돌체 크기 설정
	//collisionComp->SetCapsuleRadius(13);
	//collisionComp->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
	//collisionComp->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
	// 4. 루트로 설정
	//RootComponent = collisionComp;
	collisionComp->SetupAttachment(bodyMeshComp);

	//if (bodyMeshComp->SkeletalMesh)
	//if(bodyMeshComp->StaticMesh)
	//{
		//FVector MeshBounds = bodyMeshComp->Bounds.BoxExtent;
		//collisionComp->SetBoxExtent(MeshBounds);
	//}

	DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
	DetectionSphere->InitSphereRadius(200.f);  // 감지 범위 반경 설정
	DetectionSphere->SetupAttachment(RootComponent);

	//DetectionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);  // 쿼리 전용 충돌 설정
	//DetectionSphere->SetCollisionObjectType(ECC_WorldDynamic);
	//DetectionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	//DetectionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	// 기본 발사 모드: 단발
	//bIsAutomaticFire = false;

	// 발사 간격 설정 (예: 0.1초마다 발사)
	//FireRate = 0.1f;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::Interact_Implementation(AMyCharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("Weapon interacted with!"));
	tmpCharacter = Character;
	if (Character->WeaponSlots[Character->CurrentWeaponSlot] == nullptr)
	{
		Character->WeaponSlots[Character->CurrentWeaponSlot] = this;
		Character->CurrentWeaponAmmo = this->TotalAmmo;
		//Character->CurrentWeaponSlot = 0;
		////////////////////////////////////////
		//this->GetRootComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		//this->GetRootComponent()->SetSimulatePhysics(false);
		//this->DetectionSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		//this->DetectionSphere->SetSimulatePhysics(false);
		//this->collisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		//this->collisionComp->SetSimulatePhysics(false);
		this->SetActorEnableCollision(false);
		//////////////////////////////////////////////
		this->bodyMeshComp->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("headSocket"));
		//this->bodyMeshComp->SetRelativeLocation(FVector(-17, 10, -3));
		this->bodyMeshComp->SetRelativeRotation(FRotator(0, 0, 0));
		//this->SetActorHiddenInGame(true);
		UE_LOG(LogTemp, Warning, TEXT("Weapon picked up in Slot "));
	}
	/*
	else if(Character->WeaponSlots[1] == nullptr)
	{
		Character->WeaponSlots[1] = this;
		Character->CurrentWeaponSlot = 1;
		//this->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		this->SetActorHiddenInGame(true);
		UE_LOG(LogTemp, Warning, TEXT("Weapon picked up in Slot 2"));
	}
	*/
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Slot is full!"));
	}
}

void AWeaponBase::Fire()
{
	UE_LOG(LogTemp, Log, TEXT("Fire"));

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
		// 충돌 처리 -> 총알 파편 효과 재생
		// 총알 파편 효과 트랜스폼
		FTransform bulletTrans;
		// 부딪힌 위치 할당
		bulletTrans.SetLocation(hitInfo.ImpactPoint);
		// 총알 파편 효과 인스턴스 생성
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), bulletEffectFactory, bulletTrans);

		auto hitComp = hitInfo.GetComponent();
		// 1. 만약 컴포넌트에 물리가 적용되어 있다면
		if (hitComp && hitComp->IsSimulatingPhysics())
		{
			// 2. 날려버릴 힘과 방향이 필요
			FVector force = -hitInfo.ImpactNormal * hitComp->GetMass() * 500000;
			// 3. 그 방향으로 날려버리고 싶다.
			hitComp->AddForce(force);
		}

		// 부딪힌 대상이 적인지 판단하기
		auto enemy = hitInfo.GetActor()->GetDefaultSubobjectByName(TEXT("FSM"));
		if (enemy)
		{
			auto enemyFSM = Cast<UEnemyFSM>(enemy);
			enemyFSM->OnDamageProcess(Damage);
		}
	}
}