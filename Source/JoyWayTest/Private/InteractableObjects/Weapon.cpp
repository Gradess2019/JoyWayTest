// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObjects/Weapon.h"


AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	SetMobility(EComponentMobility::Movable);
	SetSimulatePhysics(true);
}

void AWeapon::SetSimulatePhysics(const bool& InState)
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
	GLog->Log("START FIRE");
}

void AWeapon::StopAction_Implementation()
{
	GLog->Log("STOP FIRE");
}
