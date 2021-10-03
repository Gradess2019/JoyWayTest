// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickupable.h"
#include "Engine/StaticMeshActor.h"
#include "Weapon.generated.h"

//~ Begin forward declarations
class UWeaponPrimaryDataAsset;
//~ End forward declarations

/**
 * @brief Represents a weapon in a game
 */
UCLASS(Blueprintable, BlueprintType)
class JOYWAYTEST_API AWeapon : public AStaticMeshActor, public IPickupable
{
	GENERATED_BODY()

public:
	AWeapon();

	virtual void BeginPlay() override;

	/**
	 * @brief Whether enable or disable physics simulation
	 * @param InState New physics state
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "JoyWay|InteractableObjects|Weapon"
	)
	void SetSimulatePhysics(bool InState);

	//~ Begin IInteractable interface
	virtual void Pickup_Implementation(USceneComponent* InComponent) override;
	virtual void Drop_Implementation() override;
	virtual void RunAction_Implementation() override;
	virtual void StopAction_Implementation() override;
	//~ End IInteractable interface

	/**
	 * @brief Sets new fire mode
	 * @param InFireMode New fire mode for the weapon
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "JoyWay|InteractableObjects|Weapon"
	)
	void SetFireMode(
		UPARAM(DisplayName = "FireMode") UObject* InFireMode
	);

	/**
	* @brief Sets new fire mode by class
	* @param InFireModeClass New fire mode class for the weapon
	*/
	UFUNCTION(
		BlueprintCallable,
		Category = "JoyWay|InteractableObjects|Weapon"
	)
	void SetFireModeByClass(
		UPARAM(DisplayName = "FireMode") UClass* InFireModeClass
	);

	/**
	* @brief Execute single fire
	*/
	UFUNCTION(
		BlueprintNativeEvent,
		Category = "JoyWay|InteractableObjects|Weapon|FireMode"
	)
	void Fire();

	/**
	 * @brief Execute single fire on a server
	 */
	UFUNCTION(
		Server,
		WithValidation,
		Reliable,
		Category = "JoyWay|InteractableObjects|Weapon|FireMode"
	)
	void Fire_Server();

	/**
	 * @brief Launch a trace from fire location
	 * @return Hit line-trace result
	 */
	UFUNCTION()
	FHitResult LaunchTrace();

	/**
	 * @brief Draw a trace using hit data
	 * @param Hit Used hit to draw trace
	 * @param Color Trace color
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "JoyWay|InteractableObjects|Weapon|Debug"
	)
	void DrawTrace(
		const FHitResult Hit,
		const FColor Color = FColor::Red
	);
	
	/**
	 * @brief Draw a trace on a client using hit data
	 * @param Hit Used hit to draw trace
	 * @param Color Trace color
	 */
	UFUNCTION(
		Client,
		Unreliable
	)
	void DrawTrace_Client(
		const FHitResult Hit,
		const FColor Color = FColor::Red
	);

	/**
	 * @brief Default weapon data such as fire rate, max ammo in the magazine, etc.  
	 */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly,
		Category = "JoyWay|InteractableObjects|Weapon"
	)
	UWeaponPrimaryDataAsset* DefaultData;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	/**
	 * @brief Current weapon fire mode
	 */
	UPROPERTY(
		BlueprintReadOnly,
		Category = "JoyWay|InteractableObjects|Weapon"
	)
	UObject* FireMode;

private:
	/**
	 * @brief Default collision params for single line trace while firing
	 */
	FCollisionQueryParams CollisionParams;
};
