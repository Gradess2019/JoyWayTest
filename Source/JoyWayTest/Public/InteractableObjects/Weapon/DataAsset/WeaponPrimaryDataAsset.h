// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponPrimaryDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class JOYWAYTEST_API UWeaponPrimaryDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

	UWeaponPrimaryDataAsset();

public:
	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly
	)
	UStaticMesh* Mesh;

	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly
	)
	UObject* DefaultFireMode;

	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly
	)
	FName FireLocationSocketName;

	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly
	)
	float FireRate;
	
	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly
	)
	int32 MagazineAmmo;
	
	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly
	)
	int32 Ammo;
};
