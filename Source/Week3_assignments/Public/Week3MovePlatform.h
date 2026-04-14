// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Week3MovePlatform.generated.h"

UCLASS()
class WEEK3_ASSIGNMENTS_API AWeek3MovePlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeek3MovePlatform();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform|Components")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Platform|Components")
	UStaticMeshComponent* StaticMeshComp;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Movement")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Movement")
	float MaxRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Movement")
	FVector MoveDirection;

	FVector StartLocation;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void UpdateMovement(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
