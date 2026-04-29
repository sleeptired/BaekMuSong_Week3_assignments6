// Fill out your copyright notice in the Description page of Project Settings.

#include "Week3MovePlatform.h"

AWeek3MovePlatform::AWeek3MovePlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

}

void AWeek3MovePlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	if (!Settings.MoveDirection.IsNearlyZero())
	{
		Settings.MoveDirection.Normalize();
	}
}

void AWeek3MovePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateMovement(DeltaTime);
}

void AWeek3MovePlatform::SetPlatformSettings(const FMovePlatformSettings& NewSettings)
{
	// 구조체째로 덮어쓰기
	Settings = NewSettings;

	if (!Settings.MoveDirection.IsNearlyZero())
	{
		Settings.MoveDirection.Normalize();
	}
}

void AWeek3MovePlatform::UpdateMovement(float DeltaTime)
{
	//현재위치
	FVector CurrentLocation = GetActorLocation();

	// 방향 * 속도 * 시간
	FVector DeltaLocation = Settings.MoveDirection * Settings.MoveSpeed * DeltaTime;

	//계산한 DeltaLocation 움직임
	AddActorWorldOffset(DeltaLocation, true);

	//이동한 누적 거리 검사 (출발했던 위치와 지금 위치 사이의 직선거리를 계산
	float DistanceMoved = FVector::Distance(StartLocation, CurrentLocation);

	//최종 목적지에 도달했는지 검사
	if (DistanceMoved >= Settings.MaxRange)
	{
		//초과 이동량 보정(프레임 때문에 MaxRange에 멈추지 못하고 넘어가 버리는 경우를 대비해 오차를 구함)
		float Overshoot = DistanceMoved - Settings.MaxRange;

		// 넘어간 거리만큼 반대 방향으로 되돌려보낼 벡터 생성
		FVector Correction = -Settings.MoveDirection * Overshoot;

		//그만큼 다시 보냄
		AddActorWorldOffset(Correction, true);

		// 방향 반전
		Settings.MoveDirection *= -1.0f;

		// 왕복 기준점 갱신 (다시 출발해야해서 현재위치를 시작지점으로 설정)
		StartLocation = GetActorLocation();
	}
}

FMovePlatformSettings::FMovePlatformSettings()
{
	MoveSpeed = 300.0f;
	MaxRange = 1000.0f;
	MoveDirection = FVector(1.0f, 0.0f, 0.0f);
}
