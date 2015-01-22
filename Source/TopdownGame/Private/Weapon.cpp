// Fill out your copyright notice in the Description page of Project Settings.

#include "TopdownGame.h"
#include "Weapon.h"


AWeapon::AWeapon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//SceneComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("SceneComponent"));
	//RootComponent = SceneComponent;

	if (WeaponMeshComponent == NULL)
	{
		WeaponMeshComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("WeaponMesh"));
		WeaponMeshComponent->SetSimulatePhysics(true);
		WeaponMeshComponent->SetMobility(EComponentMobility::Movable);
		RootComponent = WeaponMeshComponent;
		//WeaponMeshComponent->AttachTo(SceneComponent);
	}
	
	ShootInterval = 0.1f;
	AmmoCount = 200;
	MaxAmmo = 1000;
}

void AWeapon::OnConstruction(const FTransform& Transform)
{
	WeaponMeshComponent->SetStaticMesh(WeaponMesh);
	//WeaponMeshComponent->SetRelativeTransform(MeshTransform);
}
