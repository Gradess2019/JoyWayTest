// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FireMode.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UFireMode : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class JOYWAYTEST_API IFireMode
{
	GENERATED_BODY()

public:
	UFUNCTION(
		BlueprintNativeEvent,
		BlueprintCallable,
		Category = "JoyWay|InteractableObjects|Weapon|FireMode"
	)
	void Init(AWeapon* Weapon);

	UFUNCTION(
		BlueprintNativeEvent,
		BlueprintCallable,
		Category = "JoyWay|InteractableObjects|Weapon|FireMode"
	)
	void StartFire();

	UFUNCTION(
		BlueprintNativeEvent,
		BlueprintCallable,
		Category = "JoyWay|InteractableObjects|Weapon|FireMode"
	)
	void StopFire();
};
