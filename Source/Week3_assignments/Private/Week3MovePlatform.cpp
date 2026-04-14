// Fill out your copyright notice in the Description page of Project Settings.


#include "Week3MovePlatform.h"

// Sets default values
AWeek3MovePlatform::AWeek3MovePlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	MoveSpeed = 300.0f;          // 이동속도 
	MaxRange = 1000.0f;          // 이동할 거리 (도착지점)
	MoveDirection = FVector(1.0f, 0.0f, 0.0f); // X축 방향으로 이동 (Y,Z 원하는 방향으로 선택가능)
}

// Called when the game starts or when spawned
void AWeek3MovePlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	//MoveDirection 0,0,0이면
	if (!MoveDirection.IsNearlyZero())
	{
		MoveDirection.Normalize(); // 방향 벡터의 길이를 무조건 1로 만듦 
	}
}

// Called every frame
void AWeek3MovePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateMovement(DeltaTime);
}

void AWeek3MovePlatform::UpdateMovement(float DeltaTime)
{
	// 1. 현재 위치 가져오기
	FVector CurrentLocation = GetActorLocation();

	// 2. 이동할 양 계산 (방향 * 속도 * 시간)
	FVector DeltaLocation = MoveDirection * MoveSpeed * DeltaTime;

	// 3. 이동 적용! 
	AddActorWorldOffset(DeltaLocation, true);

	// 4. 왕복 체크 
	// 시작 위치와 현재 위치의 거리가 MaxRange를 넘었는지 확인
	float DistanceMoved = FVector::Distance(StartLocation, CurrentLocation);

	if (DistanceMoved >= MaxRange)
	{
		//  허용 범위를 넘어가면 방향 반대

		// 1. 얼마나 선을 넘었는지 계산 (예: 1015 - 1000 = 15 오버)
		float Overshoot = DistanceMoved - MaxRange;

		// 2. 선을 넘은 만큼 뒤로 다시 밀어넣어 줍니다.
		FVector Correction = -MoveDirection * Overshoot;
		AddActorWorldOffset(Correction, true);

		// 3. 끝점에 도달했으니 방향을 반전시킵니다.
		MoveDirection *= -1.0f;

		// 4.돌아갈 때를 대비해 기준점을 방금 도달한 끝점으로 갱신합니다!
		// 처음 위치 <-> 끝 위치 사이만 정확하게 왕복
		StartLocation = GetActorLocation();

		
	}
}
