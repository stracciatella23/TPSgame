// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Vehicle/MyVehicle.h"
#include "Camera/CameraComponent.h"
#include <GameFramework/SpringArmComponent.h>
#include <Components/BoxComponent.h>
#include <Components/SphereComponent.h>
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "ChaosWheeledVehicleMovementComponent.h"

AMyVehicle::AMyVehicle()
{
	DetectionComponent = CreateDefaultSubobject<UPlayerDetectionComponent>(TEXT("DetectionComponent"));

	// ���̷�Ż �޽� �ҷ�����
	/*
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/VehicleVarietyPack/Skeletons/SK_Hatchback.SK_Hatchback'"));
	if (TempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TempMesh.Object);
		//GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}
	*/

	if (GetMesh()->SkeletalMesh)
	{
		FVector MeshBounds = GetMesh()->Bounds.BoxExtent;
		collisionComp->SetBoxExtent(MeshBounds);
	}

	// 3��Ī ī�޶�
	// 1.springarm
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetRelativeLocation(FVector(0, 0, 210));
	springArmComp->TargetArmLength = 600;
	springArmComp->bUsePawnControlRotation = true;
	// 2.ī�޶�
	tpsCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("TpsCamComp"));
	tpsCamComp->SetupAttachment(springArmComp);
	tpsCamComp->bUsePawnControlRotation = false;


	collisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	collisionComp->SetCollisionProfileName(TEXT("BlockAll"));
	collisionComp->SetupAttachment(RootComponent);

	DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
	DetectionSphere->InitSphereRadius(200.f);  // ���� ���� �ݰ� ����
	DetectionSphere->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AMyVehicle::BeginPlay()
{
	Super::BeginPlay();

	auto pc = Cast<APlayerController>(Controller);
	if (pc)
	{
		auto subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
		if (subsystem)
		{
			subsystem->AddMappingContext(imc_Vehicle, 0);
		}
	}
}

// Called to bind functionality to input
void AMyVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto PlayerInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (PlayerInput)
	{
		UE_LOG(LogTemp, Warning, TEXT("MyVehicle PlayerInput"));
		PlayerInput->BindAction(ia_Turn, ETriggerEvent::Triggered, this, &AMyVehicle::Turn);
		PlayerInput->BindAction(ia_LookUp, ETriggerEvent::Triggered, this, &AMyVehicle::LookUp);
		PlayerInput->BindAction(ia_ExitCar, ETriggerEvent::Started, this, &AMyVehicle::ExitCar);

		// ���� �Է� ���ε�
		//PlayerInput->BindAction(ia_MoveForward, ETriggerEvent::Triggered, this, &AMyVehicle::MoveForward);

		// ���� �Է� ���ε�
		//PlayerInput->BindAction(ia_MoveRight, ETriggerEvent::Triggered, this, &AMyVehicle::MoveRight);

		// �극��ũ �Է� ���ε� (�ʿ� ��)
		//PlayerInput->BindAction(ia_Brake, ETriggerEvent::Triggered, this, &AMyVehicle::ApplyBrake);

	}

	//PlayerInputComponent->BindAxis("MoveForward", this, &AVehicleBase::MoveForward);
	//PlayerInputComponent->BindAxis("MoveRight", this, &AVehicleBase::MoveRight);
}

void AMyVehicle::Interact_Implementation(AMyCharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("Vehicle interacted with!"));

	if (Character->inCar)
	{
		//ExitCar(Character);
	}
	else
	{
		EnterCar(Character);
	}
}

void AMyVehicle::EnterCar(AMyCharacter* Character)
{
	Character->SetActorHiddenInGame(true);
	/*
	if (Character->WeaponSlots[Character->CurrentWeaponSlot])
	{
		Character->WeaponSlots[Character->CurrentWeaponSlot]->
	}
	*/
	Character->SetActorEnableCollision(false);
	tmpCharacterPtr = Character;
	APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
	if (PlayerController)
	{
		PlayerController->Possess(this);
		Character->inCar = true;
		// ������ RearCamera�� ī�޶� ��ȯ
		PlayerController->SetViewTargetWithBlend(this, 0.5f);  // �ε巯�� ��ȯ�� ���� BlendTime ����

		//////////////////////////////////////////////////////////////////////////////////////////
		/*
		auto pc = Cast<APlayerController>(Controller);
		if (pc)
		{
			auto subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
			if (subsystem)
			{
				subsystem->AddMappingContext(imc_Vehicle, 0);
			}
		}
		*/
		////////////////////////////////////////////////////////////////////////////////////////
	}
}

void AMyVehicle::ExitCar()
{
	UE_LOG(LogTemp, Warning, TEXT("Exit Car"));
	APlayerController* PlayerController = Cast<APlayerController>(this->GetController());
	if (PlayerController)
	{
		PlayerController->Possess(tmpCharacterPtr);
		tmpCharacterPtr->inCar = false;
		PlayerController->SetViewTargetWithBlend(tmpCharacterPtr, 0.5f);
		tmpCharacterPtr->SetActorHiddenInGame(false);
		tmpCharacterPtr->SetActorEnableCollision(true);

		FVector Start = GetActorLocation() - GetActorRightVector() * 300.0f;
		FVector End = Start - FVector(0, 0, 500.0f);  // �Ʒ� �������� 500 ���� Ʈ���̽�

		FHitResult HitResult;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		//WeaponToDrop->bodyMeshComp->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		// ���⸦ �÷��̾� ���ʿ� ��ġ
		//WeaponToDrop->SetActorLocation(DropLocation);
		//WeaponToDrop->SetActorRotation(DropRotation);

		if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params))
		{
			// �ٴ� ��ġ�� ���� ��ġ
			tmpCharacterPtr->SetActorLocation(HitResult.Location);
			//tmpCharacterPtr->SetActorRotation(FRotator(0, GetActorRotation().Yaw, 0));  // ������ Yaw ȸ���� ĳ���Ϳ� ����
		}
		else
		{
			// �ٴ��� �������� ���� ��� �⺻ ��ġ ����
			FVector DropLocation = GetActorLocation() + GetActorForwardVector() * 300.0f;
			tmpCharacterPtr->SetActorLocation(DropLocation);
		}
	}

}

void AMyVehicle::Turn(const FInputActionValue& inputValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Vehicle Turn!!"));
	float value = inputValue.Get<float>();
	AddControllerYawInput(value);
}

void AMyVehicle::LookUp(const FInputActionValue& inputValue)
{
	float value = inputValue.Get<float>();
	AddControllerPitchInput(value);
}

void AMyVehicle::MoveForward(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Vehicle MoveForward!!"));
	float ThrottleValue = Value.Get<float>();
	UChaosWheeledVehicleMovementComponent* VehicleMovement = Cast<UChaosWheeledVehicleMovementComponent>(GetVehicleMovementComponent());
	//auto VehicleMovement = GetVehicleMovementComponent();
	if (VehicleMovement)
	{
		VehicleMovement->SetThrottleInput(ThrottleValue);
	}
}

void AMyVehicle::MoveRight(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Vehicle MoveRight!!"));
	float SteeringValue = Value.Get<float>();
	UChaosWheeledVehicleMovementComponent* VehicleMovement = Cast<UChaosWheeledVehicleMovementComponent>(GetVehicleMovementComponent());
	//auto VehicleMovement = GetVehicleMovementComponent();
	if (VehicleMovement)
	{
		VehicleMovement->SetSteeringInput(SteeringValue);
	}
}

void AMyVehicle::ApplyBrake(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Vehicle Brake!!"));
	float BrakeValue = Value.Get<float>();
	UChaosWheeledVehicleMovementComponent* VehicleMovement = Cast<UChaosWheeledVehicleMovementComponent>(GetVehicleMovementComponent());
	//auto VehicleMovement = GetVehicleMovementComponent();
	if (VehicleMovement)
	{
		VehicleMovement->SetBrakeInput(BrakeValue);
	}
}