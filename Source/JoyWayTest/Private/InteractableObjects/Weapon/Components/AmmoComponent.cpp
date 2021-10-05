// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObjects/Weapon/Components/AmmoComponent.h"

#include "InteractableObjects/Weapon.h"
#include "InteractableObjects/Weapon/DataAsset/WeaponPrimaryDataAsset.h"

//~ Begin log
DEFINE_LOG_CATEGORY(LogAmmoComponent)
//~ End log

UAmmoComponent::UAmmoComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	
	SetIsReplicatedByDefault(true);
}

void UAmmoComponent::BeginPlay()
{
	Super::BeginPlay();

	// TODO: Replace with an interface
	const auto Weapon = Cast<AWeapon>(GetOwner());
	DefaultData = Weapon->DefaultData;

	Weapon->OnFire.AddDynamic(this, &UAmmoComponent::UAmmoComponent::OnFire);
	
	if (GetOwner()->HasAuthority())
	{
		CurrentMagazineAmmo = DefaultData->MagazineAmmo;
		CurrentStoreAmmo = DefaultData->StoreAmmo;
	}
}

bool UAmmoComponent::IsReloading()
{
	return TimerReload.IsValid();
}

bool UAmmoComponent::IsMagazineEmpty()
{
	return CurrentMagazineAmmo == 0;
}

bool UAmmoComponent::IsValidAmmoCount()
{
	return DefaultData->MagazineAmmo >= CurrentMagazineAmmo && CurrentMagazineAmmo > 0;
}

void UAmmoComponent::Reload()
{
	GetWorld()->GetTimerManager().SetTimer(
		TimerReload,
		this,
		&UAmmoComponent::OnReloaded,
		DefaultData->ReloadingTime
	);
}

void UAmmoComponent::Reload_Server_Implementation()
{
	Reload();
}

void UAmmoComponent::OnReloaded()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerReload);
	if (CurrentStoreAmmo == 0) { return; }

	const auto RequiredAmmo = DefaultData->MagazineAmmo - CurrentMagazineAmmo;
	const auto ActualGottenAmmo = CurrentStoreAmmo >= RequiredAmmo ? RequiredAmmo : CurrentStoreAmmo % RequiredAmmo;

	CurrentStoreAmmo -= ActualGottenAmmo;
	CurrentMagazineAmmo += ActualGottenAmmo;

	UE_LOG(LogAmmoComponent, Log, TEXT("Server: Magazine => %d; Store => %d"), CurrentMagazineAmmo, CurrentStoreAmmo);
}

void UAmmoComponent::OnFire_Implementation()
{
	CurrentMagazineAmmo--;

	if (IsMagazineEmpty())
	{
		Reload();
	}
	
	UE_LOG(LogAmmoComponent, Log, TEXT("Server: CurrentMagazineAmmo: %d"), CurrentMagazineAmmo);
}

void UAmmoComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UAmmoComponent, CurrentMagazineAmmo);
	DOREPLIFETIME(UAmmoComponent, CurrentStoreAmmo);
}

void UAmmoComponent::OnRep_CurrentAmmoInMagazine()
{
	UE_LOG(LogAmmoComponent, Log, TEXT("Client: CurrentMagazineAmmo = %d"), CurrentMagazineAmmo);
}
