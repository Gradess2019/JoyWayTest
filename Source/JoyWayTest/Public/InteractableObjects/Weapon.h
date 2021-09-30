// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickupable.h"
#include "Engine/StaticMeshActor.h"
#include "Weapon.generated.h"

/**
 * @brief Represents a weapon in a game
 */
UCLASS(Blueprintable, BlueprintType)
class JOYWAYTEST_API AWeapon : public AStaticMeshActor, public IPickupable
{
	GENERATED_BODY()

public:
	AWeapon();

	/**
	 * @brief Whether enable or disable physics simulation
	 * @param InState New physics state
	 */
	void SetSimulatePhysics(const bool& InState);

	//~ Begin IInteractable interface
	virtual void Pickup_Implementation(USceneComponent* InComponent) override;
	virtual void Drop_Implementation() override;
	//~ End IInteractable interface
};
