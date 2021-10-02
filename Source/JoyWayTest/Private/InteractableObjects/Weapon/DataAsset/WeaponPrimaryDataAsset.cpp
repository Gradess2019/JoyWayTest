// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObjects/Weapon/DataAsset/WeaponPrimaryDataAsset.h"

#include "InteractableObjects/Weapon/FireMode/NullFireMode.h"

UWeaponPrimaryDataAsset::UWeaponPrimaryDataAsset()
{
	const ConstructorHelpers::FObjectFinder<UStaticMesh> ObjectFinder(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	
	Mesh = ObjectFinder.Succeeded() ? ObjectFinder.Object : nullptr;

	DefaultFireMode = CreateDefaultSubobject<UNullFireMode>(TEXT("FireMode"));

	FireLocationSocketName = TEXT("FireLocation");
	
	FireRate = 0.1f;

	MagazineAmmo = 30;
	Ammo = 90;
}
