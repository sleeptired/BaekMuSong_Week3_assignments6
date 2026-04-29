// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Week3DetectMine.generated.h"


USTRUCT(BlueprintType)
struct FMineTrapSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExplosionDelay; // 기본 폭발 시간

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExplosionRadius; // 기본 폭발 범위

	FMineTrapSettings();
};

UCLASS()
class WEEK3_ASSIGNMENTS_API AWeek3DetectMine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeek3DetectMine();
	void SetTrapSettings(const FMineTrapSettings& NewSettings);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 컴포넌트 구성
	UPROPERTY(VisibleAnywhere, Category = "Mine|Components")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, Category = "Mine|Components")
	UStaticMeshComponent* MineMesh; // 지뢰 본체 

	UPROPERTY(VisibleAnywhere, Category = "Mine|Components")
	class USphereComponent* TriggerSphere; // 감지 및 폭발 범위

	UPROPERTY(VisibleAnywhere, Category = "Mine|Components")
	UStaticMeshComponent* RangeIndicator;

	// 설정값
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mine|Settings")
	FMineTrapSettings Settings;

	// 상태 관리
	bool bIsTriggered; 
	FTimerHandle ExplosionTimerHandle;

	// 이벤트 함수
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Explode();

public:	

	virtual void Tick(float DeltaTime) override;

};
