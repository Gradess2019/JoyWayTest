// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Net/UnrealNetwork.h"
#include "AmmoComponent.generated.h"

//~ Begin log
DECLARE_LOG_CATEGORY_EXTERN(LogAmmoComponent, Log, All);

//~ End log

//~ Begin forward declarations
class UWeaponPrimaryDataAsset;
//~ End forward declarations

/**
 * @brief Component that is responsible for ammo management
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class JOYWAYTEST_API UAmmoComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAmmoComponent();

	virtual void BeginPlay() override;

	/**
	 * @brief Checks if reload is processing
	 * @return true if reloading, false otherwise
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "JoyWay|AmmoComponent"
	)
	bool IsReloading();

	/**
	 * @brief Checks if magazine is empty
	 * @return true if empty, false otherwise
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "JoyWay|AmmoComponent"
	)
	bool IsMagazineEmpty();

	/**
	 * @brief Checks that weapon has a valid value
	 * @return true if success, false otherwise
	 */
	UFUNCTION(
		BlueprintCallable,
		Category = "JoyWay|AmmoComponent"
	)
	bool IsValidAmmoCount();

	/**
	* @brief Starts a timer for ammo reloading
	*/
	UFUNCTION(
		BlueprintCallable,
		BlueprintAuthorityOnly,
		Category = "JoyWay|AmmoComponent"
	)
	void Reload();

	/**
	 * @brief Reload weapon on the server
	 */
	UFUNCTION(
		Server,
		Reliable,
		Category = "JoyWay|AmmoComponent"
	)
	void Reload_Server();

protected:
	/**
	* @brief Fires when ammo was reloaded
	*/
	UFUNCTION(
		BlueprintCallable,
		Category = "JoyWay|AmmoComponent"
	)
	void OnReloaded();

	/**
	 * @brief Fires when weapon fired
	 */
	UFUNCTION(
		BlueprintNativeEvent,
		Category = "JoyWay|AmmoComponent"
	)
	void OnFire();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_CurrentAmmoInMagazine();

protected:
	/**
	* @brief Current amount of ammo in a mag
	*/
	UPROPERTY(
		BlueprintReadWrite,
		ReplicatedUsing=OnRep_CurrentAmmoInMagazine,
		Category = "JoyWay|AmmoComponent"
	)
	int CurrentMagazineAmmo;

	/**
	* @brief Current amount of ammo in a store
	*/
	UPROPERTY(
		BlueprintReadWrite,
		Replicated,
		Category = "JoyWay|AmmoComponent"
	)
	int CurrentStoreAmmo;

	/**
	* @brief Timer for weapon ammo reloading
	*/
	UPROPERTY()
	FTimerHandle TimerReload;

	/**
	* @brief Default weapon data such as fire rate, max ammo in the magazine, etc.  
	*/
	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly,
		Replicated,
		Category = "JoyWay|AmmoComponent",
		meta = (ExposeOnSpawn = true)
	)
	UWeaponPrimaryDataAsset* DefaultData;
};
