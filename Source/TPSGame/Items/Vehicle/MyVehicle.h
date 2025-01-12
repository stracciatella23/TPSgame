// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "Items/BaseInteractive.h"
#include "Items/PlayerDetectionComponent.h"
#include "MyVehicle.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAME_API AMyVehicle : public AWheeledVehiclePawn, public IBaseInteractive
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	AMyVehicle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 감지를 위한 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* DetectionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPlayerDetectionComponent* DetectionComponent;

	// Collision 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = Collision)
	class UBoxComponent* collisionComp;

	virtual void Interact_Implementation(AMyCharacter* Character) override;

	// 자동차에 탑승하기 위한 함수
	void EnterCar(AMyCharacter* Character);

	// 자동차에서 내리기 위한 함수
	//void ExitCar(AMyCharacter* Character);
	UFUNCTION(BlueprintCallable, Category = "MyFunctions")
	void ExitCar();

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* springArmComp;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* tpsCamComp; // 3인칭 카메라

	// 좌우 회전 입력 처리
	void Turn(const struct FInputActionValue& inputValue);
	// 상하 회전 입력 처리
	void LookUp(const struct FInputActionValue& inputValue);

	void MoveForward(const FInputActionValue& Value);

	void MoveRight(const FInputActionValue& Value);

	void ApplyBrake(const FInputActionValue& Value);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* imc_Vehicle;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_LookUp;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_Turn;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_MoveForward;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_MoveRight;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_Brake;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_ExitCar;

	class AMyCharacter* tmpCharacterPtr;
};
