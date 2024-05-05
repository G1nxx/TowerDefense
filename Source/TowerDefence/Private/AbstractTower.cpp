// Fill out your copyright notice in the Description page of Project Settings.


#include "AbstractTower.h"

// Sets default values
AAbstractTower::AAbstractTower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAbstractTower::BeginPlay()
{
	ThisRotation = this->GetActorRotation();
	ThisLocation = this->GetActorLocation();
	ShootingSpeed = 0.4;
	RotationSpeed = 0;
	CostOfUpgrading = 20;
	LevelOfTower = 1;
	isShooting = false;


	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(timer, this, &AAbstractTower::shoot, ShootingSpeed, false); 
	GetWorldTimerManager().SetTimer(rotateTimer, this, &AAbstractTower::rotateObject, WORLD_FRAME_SPEED, true);
	
}

// Called every frame
void AAbstractTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAbstractTower::UpdateLevel()
{
	this->RotationSpeed *= 1.1;
	this->ShootingSpeed /= 1.12;
	this->CostOfUpgrading *= 1.8;
	LevelOfTower++;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Enemy Destroyed"));
}

void AAbstractTower::rotateRight() {
	if (abs(TempRotation.Yaw - ThisRotation.Yaw) > ROTATION_CONST * ROTATION_ANGLE_RIGHT)
	{
		ThisRotation.Yaw -= RotationSpeed * ROTATION_ANGLE_RIGHT;
		SetActorRotation(ThisRotation);
		isShooting = false;
	}
	else
	{
		isShooting = true;
	}
}


void AAbstractTower::rotateLeft() {
	if (abs(TempRotation.Yaw - ThisRotation.Yaw) > -ROTATION_CONST * ROTATION_ANGLE_LEFT)
	{
		ThisRotation.Yaw -= RotationSpeed * ROTATION_ANGLE_LEFT;
		SetActorRotation(ThisRotation);
		isShooting = false;
	}
	else
	{
		isShooting = true;
	}
}

void AAbstractTower::rotateObject()
{
	if (AllEnemies.Num() > 0)
	{
		FVector EnemyLocation = AllEnemies[0]->GetActorLocation();

		if (EnemyLocation.X > 0 && EnemyLocation.Y > 0)
		{
			TempRotation = ThisRotation;
			TempRotation.Yaw = UKismetMathLibrary::RInterpTo(ThisRotation, UKismetMathLibrary::FindLookAtRotation(ThisLocation, EnemyLocation), UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), RotationSpeed).Yaw;
			TempRotation.Normalize();
			ThisRotation.Normalize();
			if (TempRotation.Yaw - ThisRotation.Yaw > 0 && TempRotation.Yaw - ThisRotation.Yaw < 180 || TempRotation.Yaw - ThisRotation.Yaw < 0 && TempRotation.Yaw - ThisRotation.Yaw < -180) { rotateLeft(); }
			else { rotateRight(); }
		}
	}
	else
	{
		isShooting = false;
	}
}

void AAbstractTower::shoot()
{
	if (AllEnemies.Num() > 0 && isShooting)
	{
		AActor* tempBullet = GetWorld()->SpawnActor<AActor>(bullet, this->GetActorTransform());
		AAbstractBullet* Bulle = Cast<AAbstractBullet>(tempBullet);
		if (Bulle)
		{
			Bulle->levelOfDamage = LevelOfTower - 1;
			Bulle->enemy = AllEnemies[0];
		}
		GetWorldTimerManager().SetTimer(timer, this, &AAbstractTower::shoot, ShootingSpeed, false);
	}
	else
	{
		GetWorldTimerManager().SetTimer(timer, this, &AAbstractTower::shoot, 0.01, false);
	}
}

