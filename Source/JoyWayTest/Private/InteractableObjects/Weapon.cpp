// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObjects/Weapon.h"

#include "InteractableObjects/Weapon/DataAsset/WeaponPrimaryDataAsset.h"
#include "InteractableObjects/Weapon/FireMode/AutoFireMode.h"
#include "InteractableObjects/Weapon/FireMode/FireMode.h"
#include "JoyWayTest/JoyWayTest.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Net/UnrealNetwork.h"


AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	SetMobility(EComponentMobility::Movable);
	SetSimulatePhysics(true);
	GetStaticMeshComponent()->SetGenerateOverlapEvents(true);
	GetStaticMeshComponent()->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	bReplicates = true;
	bStaticMeshReplicateMovement = true;

	CollisionParams = FCollisionQueryParams::DefaultQueryParam;
	CollisionParams.TraceTag = DebugTraceTag;
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicateMovement(bStaticMeshReplicateMovement);
	}

	check(DefaultData->DefaultFireModeClass);
	SetFireModeByClass(DefaultData->DefaultFireModeClass);
	SetDefaultStaticMesh();
}

void AWeapon::SetSimulatePhysics(const bool InState)
{
	GetStaticMeshComponent()->SetSimulatePhysics(InState);
}

void AWeapon::Pickup_Implementation(USceneComponent* InComponent)
{
	check(InComponent);
	StopAction_Implementation();

	SetSimulatePhysics(false);
	AttachToComponent(InComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void AWeapon::Drop_Implementation()
{
	StopAction_Implementation();

	GetStaticMeshComponent()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	SetSimulatePhysics(true);
}

void AWeapon::RunAction_Implementation()
{
	IFireMode::Execute_StartFire(FireMode);
}

void AWeapon::StopAction_Implementation()
{
	IFireMode::Execute_StopFire(FireMode);
}

void AWeapon::SetFireMode(UObject* InFireMode)
{
	FireMode = InFireMode;
	check(FireMode && FireMode->Implements<UFireMode>());

	IFireMode::Execute_Init(FireMode, this);
}

void AWeapon::SetFireModeByClass(UClass* InFireModeClass)
{
	const auto NewFireMode = NewObject<UObject>(this, InFireModeClass);
	SetFireMode(NewFireMode);
}

void AWeapon::Fire_Implementation()
{
	const auto Hit = LaunchTrace();
	DrawTrace(Hit, FColor::Blue);

	Fire_Server();
}

void AWeapon::Fire_Server_Implementation()
{
	const auto Hit = LaunchTrace();
	DrawTrace_Client(Hit);

	if (!Hit.IsValidBlockingHit()) { return; }

	const auto DamagedActor = Hit.Actor.Get();
	const auto BaseDamage = DefaultData->Damage;
	const auto EventInstigator = UGameplayStatics::GetPlayerController(this, 0);
	const auto DamageCauser = this;
	const auto DamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
	const auto DamageEvent = FDamageEvent(DamageTypeClass);

	DamagedActor->TakeDamage(
		BaseDamage,
		DamageEvent,
		EventInstigator,
		DamageCauser
	);
}

bool AWeapon::Fire_Server_Validate()
{
	return true;
}

FHitResult AWeapon::LaunchTrace()
{
	FHitResult Hit;
	const auto StartLocation = GetStaticMeshComponent()->GetSocketLocation(DefaultData->FireLocationSocketName);
	const auto EndLocation = StartLocation + DefaultData->TraceDistance * GetActorForwardVector();

	GetWorld()->LineTraceSingleByChannel(
		Hit,
		StartLocation,
		EndLocation,
		DefaultData->TraceChannel,
		CollisionParams
	);

	return Hit;
}

void AWeapon::DrawTrace(const FHitResult Hit, const FColor Color)
{
	DrawDebugLine(
		GetWorld(),
		Hit.TraceStart,
		Hit.IsValidBlockingHit() ? Hit.Location : Hit.TraceEnd,
		Color,
		false,
		2.f
	);
}

void AWeapon::DrawTrace_Client_Implementation(const FHitResult Hit, const FColor Color)
{
	DrawTrace(Hit, Color);
}

void AWeapon::SetDefaultStaticMesh()
{
	GetStaticMeshComponent()->SetStaticMesh(DefaultData->Mesh);
}

#if WITH_EDITOR
void AWeapon::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property &&
		PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(AWeapon, DefaultData))
	{
		SetDefaultStaticMesh();
	}
}
#endif

void AWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWeapon, DefaultData);
}
