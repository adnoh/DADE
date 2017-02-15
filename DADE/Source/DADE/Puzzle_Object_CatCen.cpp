// Fill out your copyright notice in the Description page of Project Settings.

#include "DADE.h"
#include "Puzzle_Object_CatCen.h"
#include "DummyCharacter.h"
APuzzle_Object_CatCen::APuzzle_Object_CatCen()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	


	_RidingPos = CreateDefaultSubobject<UBoxComponent>(TEXT("RPos"));
	_RidingPos->SetupAttachment(RootComponent);

	/*_Box_CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AAnotherSpirit::OnOverlapBegin);
	_Box_CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AAnotherSpirit::OnOverlapEnd);*/
	_HeroActor = NULL;
	_FSM_State = FSM_CatCen_Model1::FSM_Sleep;
	_SmellOpen = false;
}

// Called when the game starts or when spawned
void APuzzle_Object_CatCen::BeginPlay()
{
	Super::BeginPlay();



}

// Called every frame
void APuzzle_Object_CatCen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	switch (_FSM_State)
	{
	case FSM_CatCen_Model1::FSM_Sleep:
		if (_bMagicActive) {
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Smell.....")));

			_FSM_State = FSM_CatCen_Model1::FSM_Open;
			_SmellOpen = true;
		}

		break;
	case FSM_CatCen_Model1::FSM_Carry:
		SetActorLocation(_HeroActor->GetActorLocation() - _RidingPos->GetComponentLocation() + GetActorLocation());
		break;
	case FSM_CatCen_Model1::FSM_Open:
		
		break;
	}
	
}

void APuzzle_Object_CatCen::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool adnonno, const FHitResult &whatitis)
{
	//ADummyCharacter* Temp = Cast<ADummyCharacter>(OtherActor);
	//if (Temp != NULL &&_fResscued == false)
	//{
	//	//무언가 여차저차해서 주인공을 따라가게 된다는 연출?
	//	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("AnyWay... Plumger decides following Hero...")));
	//	_fResscued = true;
	//	_HeroActor = Temp;
	//}
	/*if (_FSM_State == FSM_CatCen_Model1::FSM_Sleep && _bMagicActive)
	{
		ADummyCharacter* Temp = Cast<ADummyCharacter>(OtherActor);
		if (Temp != NULL)
		{
			
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Smell.....")));

			_FSM_State = FSM_CatCen_Model1::FSM_Open;
			_SmellOpen = true;
		}
	}*/
}

void APuzzle_Object_CatCen::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

