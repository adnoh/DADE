// Fill out your copyright notice in the Description page of Project Settings.

#include "DADE.h"
#include "Puzzle_Trigger.h"


// Sets default values
APuzzle_Trigger::APuzzle_Trigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger_box"));
	_TriggerBox->SetupAttachment(RootComponent);

	_Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	_Arrow->SetupAttachment(RootComponent);

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(RootComponent);


	m_TriggerID = eID_Trigger::TriggerID_Plumger;
	

	_TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APuzzle_Trigger::OnOverlapBegin);
	_TriggerBox->OnComponentEndOverlap.AddDynamic(this, &APuzzle_Trigger::OnOverlapEnd);

}

// Called when the game starts or when spawned
void APuzzle_Trigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APuzzle_Trigger::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void APuzzle_Trigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool adnonno, const FHitResult &whatitis)
{

}

void APuzzle_Trigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}