// Fill out your copyright notice in the Description page of Project Settings.

enum Dirrection {
	forward,
	left,
	right
};

#pragma once

#ifndef WORLD_FRAME_SPEED
#define WORLD_FRAME_SPEED 1.f / 60.f
#endif //WORLD_FRAME_SPEED

#define SIZE_OF_TITLE 32u
#define ROTATION_ANGLE_RIGHT_ENEMY 0.025l * MovementSpeed
#define ROTATION_ANGLE_LEFT_ENEMY -0.025l * MovementSpeed
#define ROTATION_CONST 57.2957795131f

#include "CoreMinimal.h"
#include "MainBase.h"
#include "GameFramework/Actor.h"
#include "AbstractEnemy.generated.h"

UCLASS()
class TOWERDEFENCE_API AAbstractEnemy : public AActor
{
	GENERATED_BODY()

	FVector ThisPosition;

	FRotator ThisRotation;

	FTimerHandle moveTimer;
protected:

	bool isRotatingX;
	bool isRotatingY;
	bool isMoving;

	Dirrection EnemyDirection;

	int32 IndI;

	void checkMoveEnemy();
	
public:	
	// Sets default values for this actor's properties
	AAbstractEnemy();

	TArray<FVector> ControlPoints;
	TArray<FVector> RotatePoints;

	void setIsMoving(bool branch);

	void moveEnemy();

	void rotateEnemy();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	double Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	int32 ValueForKilling;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	double MovementSpeed;

	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void TakeDamage(const int32 IncomingDamage);

	void rotateRight();
	void rotateLeft();

	UFUNCTION(BlueprintImplementableEvent, Category = "Health")
	void EnemyAtBase();

	UFUNCTION(BlueprintImplementableEvent, Category = "Health")
	void EnemyIsKilled();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
