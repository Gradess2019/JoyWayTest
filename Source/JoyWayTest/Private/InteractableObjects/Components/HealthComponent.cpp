// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObjects/Components/HealthComponent.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY(LogHealthComponent);

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	
	SetIsReplicatedByDefault(true);
	
	Health = 100.f;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamage);
	GetOwner()->OnTakePointDamage.AddDynamic(this, &UHealthComponent::OnTakePointDamage);
	GetOwner()->OnTakeRadialDamage.AddDynamic(this, &UHealthComponent::OnTakeRadialDamage);
}

void UHealthComponent::OnTakeAnyDamage_Implementation(
	AActor* DamagedActor,
	const float Damage,
	const UDamageType* DamageType,
	AController* InstigatedBy,
	AActor* DamageCauser
)
{
	DecreaseHealth(Damage);
}

void UHealthComponent::OnTakePointDamage_Implementation(
	AActor* DamagedActor,
	const float Damage,
	AController* InstigatedBy,
	FVector HitLocation,
	UPrimitiveComponent* FHitComponent,
	FName BoneName,
	FVector ShotFromDirection,
	const UDamageType* DamageType,
	AActor* DamageCauser
)
{
	DecreaseHealth(Damage);
}

void UHealthComponent::OnTakeRadialDamage_Implementation(
	AActor* DamagedActor,
	const float Damage,
	const UDamageType* DamageType,
	FVector Origin,
	FHitResult HitInfo,
	AController* InstigatedBy,
	AActor* DamageCauser
)
{
	DecreaseHealth(Damage);
}

void UHealthComponent::DecreaseHealth_Implementation(const float Amount)
{
	Health -= Amount;

	if (Health > 0) { return; }

	OnHealthZero.Broadcast();
}

float UHealthComponent::GetHealth() const
{
	return Health;
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthComponent, Health);
}

void UHealthComponent::OnRep_Health_Implementation()
{
	UE_LOG(LogHealthComponent, Log, TEXT("%s => Health is: %f"), *GetOwner()->GetName(), Health);
}
