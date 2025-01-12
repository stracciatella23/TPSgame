// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/Bazooka/Bullet.h"
#include <Components/SphereComponent.h> // USphereComponent
#include <Components/BoxComponent.h>
#include <GameFramework/ProjectileMovementComponent.h> // UProjectileMovementComponent
#include <Kismet/GameplayStatics.h>
#include <Enemy/EnemyFSM.h>
#include "Items/Weapons/Bazooka/Bazooka.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	collisionComp->SetCollisionProfileName(TEXT("BlockAll"));
	collisionComp->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
	RootComponent = collisionComp;
	//collisionComp->SetupAttachment(RootComponent);
	//collisionComp->SetSphereRadius(18);
	//collisionComp->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));

	bodyMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMeshComp"));
	bodyMeshComp->SetupAttachment(collisionComp);
	//RootComponent = bodyMeshComp;
	bodyMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//bodyMeshComp->SetRelativeScale3D(FVector(0.25f));

	// Bullet �̵� ������Ʈ
	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	// movement ������Ʈ�� ����(�̵�)��ų ������Ʈ ����
	movementComp->SetUpdatedComponent(RootComponent);
	// �ʱ�ӵ�
	movementComp->InitialSpeed = 5000;
	// �ִ� �ӵ�
	movementComp->MaxSpeed = 5000;
	// �ݵ� ����
	movementComp->bShouldBounce = true;
	// �ݵ� ��
	movementComp->Bounciness = 0.3f;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Bullet Spawned"));
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::FireInDirection(const FVector& ShootDirection)
{
	movementComp->Velocity = ShootDirection * movementComp->InitialSpeed;
}

void ABullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//Destroy();
	UE_LOG(LogTemp, Warning, TEXT("Projectile Hit Detected"));
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{

		// �浹 ó�� -> �Ѿ� ���� ȿ�� ���
		// �Ѿ� ���� ȿ�� Ʈ������
		FTransform bulletTrans;
		// �ε��� ��ġ �Ҵ�
		bulletTrans.SetLocation(Hit.ImpactPoint);
		// �Ѿ� ���� ȿ�� �ν��Ͻ� ����
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), bulletEffectFactory, bulletTrans);

		// �ε��� ����� ������ �Ǵ��ϱ�
		auto enemy = Hit.GetActor()->GetDefaultSubobjectByName(TEXT("FSM"));
		if (enemy)
		{
			auto enemyFSM = Cast<UEnemyFSM>(enemy);
			enemyFSM->OnDamageProcess(bulletdamage);
		}

		// �Ѿ� �Ҹ�
		Destroy();
	}

}