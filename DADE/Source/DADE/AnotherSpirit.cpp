// Fill out your copyright notice in the Description page of Project Settings.

#include "DADE.h"
#include "AnotherSpirit.h"
#include "DummyCharacter.h"

// Sets default values
AAnotherSpirit::AAnotherSpirit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_Box_CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	_Box_CollisionBox->SetupAttachment(RootComponent);

	_Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	_Arrow->SetupAttachment(RootComponent);

	_StaticMesh_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_StaticMesh_Mesh->SetupAttachment(RootComponent);

	
	_RidingPos = CreateDefaultSubobject<UBoxComponent>(TEXT("RPos"));
	_RidingPos->SetupAttachment(RootComponent);

	/*_Box_CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AAnotherSpirit::OnOverlapBegin);
	_Box_CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AAnotherSpirit::OnOverlapEnd);*/
	_HeroActor = NULL;
	_fResscued = false;
}

// Called when the game starts or when spawned
void AAnotherSpirit::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void AAnotherSpirit::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (_fResscued)
	{
		SetActorLocation(_HeroActor->GetActorLocation() - _RidingPos->GetComponentLocation() + GetActorLocation());
	}
}

void AAnotherSpirit::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool adnonno, const FHitResult &whatitis)
{
	ADummyCharacter* Temp = Cast<ADummyCharacter>(OtherActor);
	if (Temp != NULL &&_fResscued==false)
	{
		//무언가 여차저차해서 주인공을 따라가게 된다는 연출?
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("AnyWay... Plumger decides following Hero...")));
		_fResscued = true;
		_HeroActor = Temp;
	}
}

void AAnotherSpirit::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}