// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObjects/Weapon/DataAsset/WeaponPrimaryDataAsset.h"

#include "InteractableObjects/Weapon/FireMode/NullFireMode.h"

UWeaponPrimaryDataAsset::UWeaponPrimaryDataAsset()
{
	const ConstructorHelpers::FObjectFinder<UStaticMesh> ObjectFinder(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	
	Mesh = ObjectFinder.Succeeded() ? ObjectFinder.Object : nullptr;

	DefaultFireModeClass = UNullFireMode::StaticClass();

	FireLocationSocketName = TEXT("FireLocation");
	
	FireRate = 0.1f;
	ReloadingTime = 1.f;
	Damage = 30.f;
	TraceDistance = 10000.f;

	MagazineAmmo = 30;
	StoreAmmo = 90;

	TraceChannel = ECC_Visibility;
}
