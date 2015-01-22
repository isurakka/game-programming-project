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

	//USceneComponent* SceneComponent;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UStaticMeshComponent* WeaponMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	UStaticMesh* WeaponMesh;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	//FTransform MeshTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float ShootInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int32 AmmoCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int32 MaxAmmo;

	virtual void OnConstruction(const FTransform& Transform) override;
};
