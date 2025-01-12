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

	// ���� ������Ʈ �߰�
	DetectionComponent = CreateDefaultSubobject<UPlayerDetectionComponent>(TEXT("DetectionComponent"));

	// 5. �ܰ� ������Ʈ ����ϱ�
	//bodyMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BodyMeshComp"));
	bodyMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMeshComp"));
	// 6. �θ� ������Ʈ ����
	bodyMeshComp->SetupAttachment(collisionComp);
	RootComponent = bodyMeshComp;
	// 7. �浹 ��Ȱ��ȭ
	//bodyMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//bodyMeshComp->SetCollisionProfileName(TEXT("BloackAll"));
	// 8. �ܰ� ũ�� ����
	//bodyMeshComp->SetRelativeScale3D(FVector(0.25f));

	// 1. �浹ü ���
	collisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	// 2. �浹 �������� ����
	collisionComp->SetCollisionProfileName(TEXT("BlockAll"));
	// 3. �浹ü ũ�� ����
	//collisionComp->SetCapsuleRadius(13);
	//collisionComp->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
	//collisionComp->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
	// 4. ��Ʈ�� ����
	//RootComponent = collisionComp;
	collisionComp->SetupAttachment(bodyMeshComp);

	//if (bodyMeshComp->SkeletalMesh)
	//if(bodyMeshComp->StaticMesh)
	//{
		//FVector MeshBounds = bodyMeshComp->Bounds.BoxExtent;
		//collisionComp->SetBoxExtent(MeshBounds);
	//}

	DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
	DetectionSphere->InitSphereRadius(200.f);  // ���� ���� �ݰ� ����
	DetectionSphere->SetupAttachment(RootComponent);

	//DetectionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);  // ���� ���� �浹 ����
	//DetectionSphere->SetCollisionObjectType(ECC_WorldDynamic);
	//DetectionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	//DetectionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	// �⺻ �߻� ���: �ܹ�
	//bIsAutomaticFire = false;

	// �߻� ���� ���� (��: 0.1�ʸ��� �߻�)
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
	// Channel ���͸� �̿��� LineTrace �浹 ����(�浹 ����, ���� ��ġ, ���� ��ġ, ���� ä��, �浹 �ɼ�)
	bool bHit = GetWorld()->LineTraceSingleByChannel(hitInfo, startPos, endPos, ECC_Visibility, params);
	// LineTrace�� �ε����� ��
	if (bHit)
	{
		// �浹 ó�� -> �Ѿ� ���� ȿ�� ���
		// �Ѿ� ���� ȿ�� Ʈ������
		FTransform bulletTrans;
		// �ε��� ��ġ �Ҵ�
		bulletTrans.SetLocation(hitInfo.ImpactPoint);
		// �Ѿ� ���� ȿ�� �ν��Ͻ� ����
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), bulletEffectFactory, bulletTrans);

		auto hitComp = hitInfo.GetComponent();
		// 1. ���� ������Ʈ�� ������ ����Ǿ� �ִٸ�
		if (hitComp && hitComp->IsSimulatingPhysics())
		{
			// 2. �������� ���� ������ �ʿ�
			FVector force = -hitInfo.ImpactNormal * hitComp->GetMass() * 500000;
			// 3. �� �������� ���������� �ʹ�.
			hitComp->AddForce(force);
		}

		// �ε��� ����� ������ �Ǵ��ϱ�
		auto enemy = hitInfo.GetActor()->GetDefaultSubobjectByName(TEXT("FSM"));
		if (enemy)
		{
			auto enemyFSM = Cast<UEnemyFSM>(enemy);
			enemyFSM->OnDamageProcess(Damage);
		}
	}
}