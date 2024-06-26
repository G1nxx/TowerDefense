// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicTower.h"

// Sets default values
ABasicTower::ABasicTower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABasicTower::BeginPlay()
{
	Super::BeginPlay();
	RotationSpeed = ROTATION_CONST;
	LevelOfTower = 1;
	CostOfTower = 50;
	CostOfUpgrading = 30;
	ShootingSpeed = 1.15;
	
}

// Called every frame
void ABasicTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

