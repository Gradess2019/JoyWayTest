// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObjects/Weapon/FireMode/AutoFireMode.h"
#include "InteractableObjects/Weapon.h"
#include "InteractableObjects/Weapon/DataAsset/WeaponPrimaryDataAsset.h"

void UAutoFireMode::Init_Implementation(AWeapon* InWeapon)
{
	Weapon = InWeapon;
}

void UAutoFireMode::StartFire_Implementation()
{
	Weapon->Fire();
	GetWorld()->GetTimerManager().SetTimer(
		Timer,
		Weapon,
		&AWeapon::Fire,
		Weapon->DefaultData->FireRate,
		true
	);
}

void UAutoFireMode::StopFire_Implementation()
{
	// TODO fix bug where we can fire quickly just by clicking on trigger as fast as possible
	GetWorld()->GetTimerManager().ClearTimer(Timer);
}
