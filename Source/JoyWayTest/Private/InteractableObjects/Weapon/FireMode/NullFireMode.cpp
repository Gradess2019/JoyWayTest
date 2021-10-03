// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObjects/Weapon/FireMode/NullFireMode.h"

#define PRINT_WARNING() UE_LOG(FireModeLog, Warning, TEXT("Current weapon doesn't have a fire mode! %s::%s"), __FUNCTION__, __LINE__)

void UNullFireMode::StartFire_Implementation()
{
	PRINT_WARNING();
}

void UNullFireMode::StopFire_Implementation()
{
	PRINT_WARNING();
}
