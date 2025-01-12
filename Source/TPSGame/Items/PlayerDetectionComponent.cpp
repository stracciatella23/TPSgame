// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PlayerDetectionComponent.h"
#include "Components/SphereComponent.h" // USphereComponent
#include <Player/MyCharacter.h>
#include <Kismet/GameplayStatics.h>
#include "TimerManager.h" // TimerManager ���� ���
#include "Components/PrimitiveComponent.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "Blueprint/UserWidget.h"
#include "Items/BaseInteractive.h"

// Sets default values for this component's properties
UPlayerDetectionComponent::UPlayerDetectionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	/*
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass(TEXT("/Game/UI/WBP_Interact.WBP_Interact"));

	if (WidgetClass.Succeeded())
	{
		InteractionWidgetClass = WidgetClass.Class;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find widget class!"));
	}
	*/
	
	// ...
}


// Called when the game starts
void UPlayerDetectionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	// ������Ʈ�� ������ ������ ���� ������Ʈ ��������
	if (AActor* Owner = GetOwner())
	{
		// ������ ���� ������Ʈ�� ��������
		USphereComponent* DetectionSphere = Owner->FindComponentByClass<USphereComponent>();
		if (DetectionSphere)
		{
			// �浹 �̺�Ʈ ���ε�
			DetectionSphere->OnComponentBeginOverlap.AddDynamic(this, &UPlayerDetectionComponent::OnOverlapBegin);
			DetectionSphere->OnComponentEndOverlap.AddDynamic(this, &UPlayerDetectionComponent::OnOverlapEnd);
		}
	}
}


// Called every frame
void UPlayerDetectionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerDetectionComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMyCharacter* Player = Cast<AMyCharacter>(OtherActor))
	{
		// ���� �Լ� ȣ���� ���� Ÿ�̸� ����
		Player->GetWorldTimerManager().SetTimer(DetectionTimerHandle, this, &UPlayerDetectionComponent::CheckIfInView, 0.1f, true);
	}
}

void UPlayerDetectionComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AMyCharacter* Player = Cast<AMyCharacter>(OtherActor))
	{
		// Ÿ�̸� ����
		Player->GetWorldTimerManager().ClearTimer(DetectionTimerHandle);
		HideInteractionUI();  // ������ ����� UI ����
	}
}

void UPlayerDetectionComponent::CheckIfInView()
{
	AMyCharacter* Player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Player) return;
	
	FHitResult HitResult;
	FVector Start = Player->tpsCamComp->GetComponentLocation();
	FVector End = Start + (Player->tpsCamComp->GetForwardVector() * Player->LineTraceDetectionDistance);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Player);
	// �ü��� �ִ� ������Ʈ ����
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params))
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor && HitActor->GetClass()->ImplementsInterface(UBaseInteractive::StaticClass()))
		{
			//UE_LOG(TPS, Warning, TEXT("ui make"))
			//IBaseInteractive::Execute_Interact(HitActor, this);

			ShowInteractionUI();
		}
		//ShowInteractionUI();
		else
		{

			HideInteractionUI();
		}
		//UE_LOG(TPS, Warning, TEXT("what is this"))
		//HideInteractionUI();
	}
	else
	{
		HideInteractionUI();

		//UE_LOG(TPS, Warning, TEXT("ui hide"))
	}
	//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 5.0f, 0, 2.0f);
}

void UPlayerDetectionComponent::ShowInteractionUI()
{
	if (!InteractionWidget && InteractionWidgetClass)  // ������ ����, Ŭ������ ��ȿ�� ���� ����
	{
		InteractionWidget = CreateWidget<UUserWidget>(GetWorld(), InteractionWidgetClass);
		if (InteractionWidget)
		{
			InteractionWidget->AddToViewport();
		}
	}
	else if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Visible);  // ������ �̹� �����ϸ� ǥ�� ���·� ��ȯ
	}
}

void UPlayerDetectionComponent::HideInteractionUI()
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Hidden);  // ������ �����
	}
}
