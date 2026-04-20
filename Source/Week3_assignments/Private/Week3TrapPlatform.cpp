// Fill out your copyright notice in the Description page of Project Settings.


#include "Week3TrapPlatform.h"

// Sets default values
AWeek3TrapPlatform::AWeek3TrapPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	// 트리거 박스 세팅
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(SceneRoot);
	TriggerBox->SetBoxExtent(FVector(100.0f, 100.0f, 50.0f));
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));

	DestroyTime = 3.0f; 
}

// Called when the game starts or when spawned
void AWeek3TrapPlatform::BeginPlay()
{
	Super::BeginPlay();
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AWeek3TrapPlatform::OnOverlapBegin);
}

void AWeek3TrapPlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		//assignment6 check
		GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &AWeek3TrapPlatform::TriggerDestroy, DestroyTime, false);

		UE_LOG(LogTemp, Warning, TEXT("함정 발동! %f초 뒤 폭파!"), DestroyTime);
	}
}

void AWeek3TrapPlatform::TriggerDestroy()
{
	Destroy();
}

// Called every frame
void AWeek3TrapPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

