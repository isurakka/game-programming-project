// Fill out your copyright notice in the Description page of Project Settings.

#include "TopdownGame.h"
#include "Weapon.h"


AWeapon::AWeapon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	WeaponMeshComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("WeaponMesh"));
	RootComponent = WeaponMeshComponent;
	WeaponMeshComponent->SetStaticMesh(WeaponMesh);

	ShootInterval = 0.1f;
	AmmoCount = 200;
	MaxAmmo = 1000;
}
