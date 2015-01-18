// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNGAME_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:
	AWeapon(const FObjectInitializer& ObjectInitializer);

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	class UStaticMeshComponent* WeaponMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	UStaticMesh* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float ShootInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int32 AmmoCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int32 MaxAmmo;
};
