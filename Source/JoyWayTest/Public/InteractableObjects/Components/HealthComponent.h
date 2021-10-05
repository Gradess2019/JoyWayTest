// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

//~ Begin delegate declarations
DECLARE_LOG_CATEGORY_EXTERN(LogHealthComponent, Log, All);
//~ End delegate declarations

//~ Begin delegate declarations
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealtZeroSignature);
//~ End delegate declarations

/**
 * @brief Component that is responsible for health of the object
 */
UCLASS(
	Blueprintable,
	BlueprintType,
	ClassGroup = (
		Custom
	),
	meta = (
		BlueprintSpawnableComponent
	)
)
class JOYWAYTEST_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

	virtual void BeginPlay() override;


protected:
	UFUNCTION(
		BlueprintNativeEvent,
		Category = "JoyWay|HealthComponent"
	)
	void OnTakeAnyDamage(
		AActor* DamagedActor,
		float Damage,
		const class UDamageType* DamageType,
		class AController* InstigatedBy,
		AActor* DamageCauser
	);

	UFUNCTION(
		BlueprintNativeEvent,
		Category = "JoyWay|HealthComponent"
	)
	void OnTakePointDamage(
		AActor* DamagedActor,
		float Damage,
		class AController* InstigatedBy,
		FVector HitLocation,
		class UPrimitiveComponent* FHitComponent,
		FName BoneName,
		FVector ShotFromDirection,
		const class UDamageType* DamageType,
		AActor* DamageCauser
	);

	UFUNCTION(
		BlueprintNativeEvent,
		Category = "JoyWay|HealthComponent"
	)
	void OnTakeRadialDamage(
		AActor* DamagedActor,
		float Damage,
		const class UDamageType* DamageType,
		FVector Origin,
		FHitResult HitInfo,
		class AController* InstigatedBy,
		AActor* DamageCauser
	);

	/**
	 * @brief Decrease health
	 * @param Amount number for decreasing health
	 */
	UFUNCTION(
		BlueprintNativeEvent,
		BlueprintAuthorityOnly,
		Category = "JoyWay|HealthComponent"
	)
	void DecreaseHealth(
		float Amount
	);

	/**
	 * @brief Returns current health value
	 * @return current health
	 */
	UFUNCTION(
		BlueprintGetter,
		Category = "JoyWay|HealthComponent"
	)
	float GetHealth() const;

	virtual void GetLifetimeReplicatedProps(
		TArray<FLifetimeProperty>& OutLifetimeProps
	) const override;

	UFUNCTION(
		BlueprintNativeEvent,
		Category = "JoyWay|HealthComponent"
	)
	void OnRep_Health();

public:
	UPROPERTY(
		BlueprintAssignable,
		Category = "JoyWay|HealthComponent"
	)
	FHealtZeroSignature OnHealthZero;

private:
	/**
	 * @brief Current health
	 */
	UPROPERTY(
		EditAnywhere,
		BlueprintGetter = GetHealth,
		ReplicatedUsing = OnRep_Health,
		Category = "JoyWay|HealthComponent"
	)
	float Health;
};
