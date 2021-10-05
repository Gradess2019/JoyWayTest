// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickupable.h"
#include "Engine/StaticMeshActor.h"
#include "Weapon.generated.h"

//~ Begin forward declarations
class UWeaponPrimaryDataAsset;
class UAmmoComponent;
//~ End forward declarations

//~ Begin delegate declarations
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponFireSignature);
//~ End delegate declarations

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
		Category = "JoyWay|Weapon"
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
		Category = "JoyWay|Weapon"
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
		Category = "JoyWay|Weapon"
	)
	void SetFireModeByClass(
		UPARAM(DisplayName = "FireMode") UClass* InFireModeClass
	);

	/**
	* @brief Executes reload on ammo component
	*/
	UFUNCTION(
		BlueprintNativeEvent,
		BlueprintCallable,
		Category = "JoyWay|Weapon"
	)
	void Reload();

	/**
	* @brief Executes single fire
	*/
	UFUNCTION(
		BlueprintNativeEvent,
		Category = "JoyWay|Weapon|FireMode"
	)
	void Fire();

	/**
	 * @brief Executes single fire on a server
	 */
	UFUNCTION(
		Server,
		WithValidation,
		Reliable,
		Category = "JoyWay|Weapon|FireMode"
	)
	void Fire_Server();

	/**
	 * @brief Launches a trace from fire location
	 * @return Hit line-trace result
	 */
	UFUNCTION()
	FHitResult LaunchTrace();

	/**
	 * @brief Draws a trace using hit data
	 * @param Hit Used hit to draw trace
	 * @param Color Trace color
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "JoyWay|Weapon|Debug"
	)
	void DrawTrace(
		const FHitResult Hit,
		const FColor Color = FColor::Red
	);

	/**
	 * @brief Draws a trace on a client using hit data
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
	 * @brief Sets default static mesh
	 */
	UFUNCTION()
	void SetDefaultStaticMesh();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	bool IsDefaultDataChanged(const FPropertyChangedEvent& PropertyChangedEvent) const;
#endif

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	/**
	 * @brief Weapon fire delegate
	 */
	UPROPERTY(
		BlueprintAssignable,
		Category = "JoyWay|Weapon"
	)
	FWeaponFireSignature OnFire;

	/**
	* @brief Default weapon data such as fire rate, max ammo in the magazine, etc.  
	*/
	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly,
		Replicated,
		Category = "JoyWay|Weapon",
		meta = (ExposeOnSpawn = true)
	)
	UWeaponPrimaryDataAsset* DefaultData;

protected:
	/**
	 * @brief Current weapon fire mode
	 */
	UPROPERTY(
		BlueprintReadOnly,
		Category = "JoyWay|Weapon"
	)
	UObject* FireMode;

	/**
	 * @brief Current ammo component
	 */
	UPROPERTY(
		BlueprintReadOnly,
		Category = "JoyWay|Weapon"
	)
	UAmmoComponent* AmmoComponent;
};
