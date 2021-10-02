// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObjects/Weapon.h"

#include "InteractableObjects/Weapon/FireMode/AutoFireMode.h"
#include "InteractableObjects/Weapon/FireMode/FireMode.h"


AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	SetMobility(EComponentMobility::Movable);
	SetSimulatePhysics(true);

	// TODO Create a function to change fire mode dynamically
	FireMode = CreateDefaultSubobject<UAutoFireMode>(TEXT("FireMode"));
	IFireMode::Execute_Init(FireMode, this);
}

void AWeapon::SetSimulatePhysics(const bool InState)
{
	GetStaticMeshComponent()->SetSimulatePhysics(InState);
}

void AWeapon::Pickup_Implementation(USceneComponent* InComponent)
{
	if (!InComponent) return;

	SetSimulatePhysics(false);
	AttachToComponent(InComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void AWeapon::Drop_Implementation()
{
	GetStaticMeshComponent()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	SetSimulatePhysics(true);
}

void AWeapon::RunAction_Implementation()
{
	check(FireMode && FireMode->Implements<UFireMode>())

	IFireMode::Execute_StartFire(FireMode);
}

void AWeapon::StopAction_Implementation()
{
	check(FireMode && FireMode->Implements<UFireMode>())

	IFireMode::Execute_StopFire(FireMode);
}

void AWeapon::SetFireMode(UObject* InFireMode)
{
	FireMode = InFireMode;
}

void AWeapon::Fire_Implementation()
{
	GLog->Log("Fire!");
}
