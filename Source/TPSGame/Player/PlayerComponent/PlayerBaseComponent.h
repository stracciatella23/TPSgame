// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/MyCharacter.h"
#include "PlayerBaseComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPSGAME_API UPlayerBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerBaseComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// 사용자 입력 맵핑 처리 함수
	virtual void SetupInputBinding(class UEnhancedInputComponent* PlayerInput) {};

	// 해당 컴포넌트를 소유한 액터
	UPROPERTY()
	AMyCharacter* me;

	UPROPERTY()
	UCharacterMovementComponent* moveComp;

		
};
