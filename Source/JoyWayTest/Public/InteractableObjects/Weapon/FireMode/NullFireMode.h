// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FireMode.h"
#include "UObject/Object.h"
#include "NullFireMode.generated.h"

/**
 * @brief A null fire mode that does nothing. It can be used instead of nullptr
 */
UCLASS()
class JOYWAYTEST_API UNullFireMode : public UObject, public IFireMode
{
	GENERATED_BODY()

public:
	//~ Begin IFireMode interface
	virtual void StartFire_Implementation() override;
	virtual void StopFire_Implementation() override;
	//~ End IFireMode interface
};
