// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FireMode.h"
#include "UObject/Object.h"
#include "AutoFireMode.generated.h"

//~ Begin forward declarations
class AWeapon;
//~ End forward declarations

/**
 * @brief Represents an automatic fire mode
 */
UCLASS()
class JOYWAYTEST_API UAutoFireMode : public UObject, public IFireMode
{
	GENERATED_BODY()

public:
	//~ Begin IFireMode interface
	virtual void Init_Implementation(AWeapon* InWeapon) override;
	virtual void StartFire_Implementation() override;
	virtual void StopFire_Implementation() override;
	//~ End IFireMode interface

protected:
	/**
	 * @brief A weapon that owns this fire mode
	 */
	UPROPERTY(
		BlueprintReadOnly,
		Category = "JoyWay|InteractableObjects|Weapon|FireMode"
	)
	AWeapon* Weapon;
	
private:
	/**
	 * @brief Timer that executes Fire function on the weapon
	 */
	UPROPERTY()
	FTimerHandle Timer;
};
