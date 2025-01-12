// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MyCharacter.h"
#include <GameFramework/SpringArmComponent.h> // SpringArmComponent
#include <Camera/CameraComponent.h> // CameraComponent
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include <Kismet/GameplayStatics.h>
#include <Blueprint/UserWidget.h>
#include "PlayerComponent/PlayerCamera.h"  // PlayerCamera ������Ʈ
#include "PlayerComponent/PlayerMove.h"    // PlayerMove ������Ʈ
#include "PlayerComponent/PlayerWeapon.h" // PlayerWeapon ������Ʈ
#include "Items/BaseInteractive.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ���̷�Ż �޽� �ҷ�����
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (TempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TempMesh.Object);
		// �޽� ������Ʈ ��ġ ����
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}

	// 3��Ī ī�޶� SpringArm
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetRelativeLocation(FVector(0, 70, 90));
	springArmComp->TargetArmLength = 400;
	springArmComp->bUsePawnControlRotation = true;

	// 3��Ī ī�޶�
	tpsCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("TpsCamComp"));
	tpsCamComp->SetupAttachment(springArmComp);
	tpsCamComp->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = true;

	playerMove = CreateDefaultSubobject<UPlayerMove>(TEXT("PlayerMove"));
	playerWeapon = CreateDefaultSubobject<UPlayerWeapon>(TEXT("PlayerWeapon"));
	playerCamera = CreateDefaultSubobject<UPlayerCamera>(TEXT("PlayerCamera"));
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	auto pc = Cast<APlayerController>(Controller);
	if (pc)
	{
		auto subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
		if (subsystem)
		{
			subsystem->AddMappingContext(imc_MyProject, 0);
		}
	}
	
	crosshairUI = CreateWidget(GetWorld(), crosshairUIFactory);
	crosshairUI->AddToViewport();

	HP = initialHP;
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �̵� ó��
	Move();

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto PlayerInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (PlayerInput)
	{
		// ������Ʈ���� �Է� ���ε� ó���ϵ��� ȣ��
		playerMove->SetupInputBinding(PlayerInput);
		playerWeapon->SetupInputBinding(PlayerInput);
		playerCamera->SetupInputBinding(PlayerInput);

		// ������ �ݱ�
		PlayerInput->BindAction(ia_Interact, ETriggerEvent::Started, this, &AMyCharacter::Interact);
	}
}

void AMyCharacter::Move()
{
	// �÷��̾� �̵� ó��
	direction = FTransform(GetControlRotation()).TransformVector(direction);
	AddMovementInput(direction);
	direction = FVector::ZeroVector;
}

void AMyCharacter::OnHitEvent()
{
	UE_LOG(LogTemp, Log, TEXT("My Character Damaged"));

	HP--;
	if (HP <= 0)
	{
		UE_LOG(LogTemp, Log, TEXT("My Character Dead"));
		OnGameOver();
	}

}

void AMyCharacter::YouWin_Implementation()
{
	//�¸� ���� �� �Ͻ� ����
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void AMyCharacter::OnGameOver_Implementation()
{
	//���� ���� �� �Ͻ� ����
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void AMyCharacter::Interact()
{
	FHitResult HitResult;
	FVector Start = tpsCamComp->GetComponentLocation();
	FVector End = Start + (tpsCamComp->GetForwardVector() * LineTraceDetectionDistance);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	// �ü��� �ִ� ������Ʈ ����
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params))
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor && HitActor->GetClass()->ImplementsInterface(UBaseInteractive::StaticClass()))
		{
			IBaseInteractive::Execute_Interact(HitActor, this);
		}
	}
}
