// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Pickupable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPickupable : public UInterface
{
	GENERATED_BODY()
};

/**
 * @brief Represents an object that can be picked up by someone such as player
 */
class JOYWAYTEST_API IPickupable
{
	GENERATED_BODY()

public:
	/**
	 * @brief Attaches object to component
	 * @param InComponent Component to attach to
	 */
	UFUNCTION(
		BlueprintNativeEvent,
		BlueprintCallable,
		Category = "JoyWay|InteractableObjects|Interactable"
	)
	void Pickup(
		UPARAM(DisplayName = "Component") USceneComponent* InComponent
	);

	/**
	 * @brief Detaches object
	 */
	UFUNCTION(
		BlueprintNativeEvent,
		BlueprintCallable,
		Category = "JoyWay|InteractableObjects|Interactable"
	)
	void Drop();
};
