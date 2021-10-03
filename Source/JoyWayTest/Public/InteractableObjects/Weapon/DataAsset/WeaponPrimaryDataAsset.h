// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponPrimaryDataAsset.generated.h"

//~ Begin forward declarations
class UFireMode;
//~ End forward declarations

/**
 * @brief A data asset that contains default information about weapon such as fire mode, ammo, etc. 
 */
UCLASS()
class JOYWAYTEST_API UWeaponPrimaryDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

	UWeaponPrimaryDataAsset();

public:
	/**
	 * @brief Weapon mesh
	 */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly
	)
	UStaticMesh* Mesh;

	/**
	 * @brief Weapon default fire mode like a automatic, semi-auto, etc.
	 */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly,
		meta = (
			MustImplement = "FireMode"
		)
	)
	TSubclassOf<UObject> DefaultFireModeClass;

	/**
	 * @brief From where we will start our line trace
	 */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly
	)
	FName FireLocationSocketName;

	/**
	 * @brief Delay between every single shot
	 */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly
	)
	float FireRate;
	
	/**
	 * @brief Amount of damage that we apply on hit actor
	 */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly
	)
	float Damage;

	/**
	 * @brief How far the end of line trace will be from fire location socket
	 */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly
	)
	float TraceDistance;

	/**
	 * @brief Max ammo in a magazine
	 */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly
	)
	int32 MagazineAmmo;

	/**
	 * @brief Max ammo in a store
	 */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly
	)
	int32 Ammo;

	/**
	 * @brief Channel for line trace to detect hit
	 */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly
	)
	TEnumAsByte<ECollisionChannel> TraceChannel;
};
