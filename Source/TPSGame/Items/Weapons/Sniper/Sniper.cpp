// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/Sniper/Sniper.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"

ASniper::ASniper()
{
	bIsSniperMode = false;
}

void ASniper::BeginPlay()
{
	Super::BeginPlay();
	sniperUI = CreateWidget(GetWorld(), sniperUIFactory);
}

void ASniper::SniperMode()
{
	//UE_LOG(LogTemp, Log, TEXT("SniperMode!"));

	if (bIsSniperMode)
	{
		bIsSniperMode = false;
		//tmpCharacter->sniperUI->RemoveFromParent();
		sniperUI->RemoveFromParent();
		
		tmpCharacter->tpsCamComp->SetFieldOfView(90.0f);
		
		
	}
	else
	{
		bIsSniperMode = true;
		//tmpCharacter->sniperUI->AddToViewport();
		sniperUI->AddToViewport();
		
		tmpCharacter->tpsCamComp->SetFieldOfView(45.0f);
		
	}

}

