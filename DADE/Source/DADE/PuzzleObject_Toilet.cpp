// Fill out your copyright notice in the Description page of Project Settings.

#include "DADE.h"
#include "PuzzleObject_Toilet.h"
#include "DummyCharacter.h"




APuzzleObject_Toilet::APuzzleObject_Toilet()
{
	_FSM_Status = FSM_Toilet_Model1::FSM_Sleep;

	_UpperMeshSpindle = CreateDefaultSubobject<UBoxComponent>(TEXT("Spindle"));
	_UpperMeshSpindle->SetupAttachment(RootComponent);
}
APuzzleObject_Toilet::~APuzzleObject_Toilet()
{

}

void APuzzleObject_Toilet::BeginPlay()
{
	Super::BeginPlay();
	APuzzle_Object::BeginPlay();


}

// Called every frame
void APuzzleObject_Toilet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Dir;

	FRotator NewRotation;

	if (_bMagicActive) {
		switch (_FSM_Status)
		{
		case FSM_Toilet_Model1::FSM_Sleep:
			break;
		case FSM_Toilet_Model1::FSM_Moving:
			
			NewRotation = FMath::RInterpTo(_UpperMeshSpindle->GetRelativeTransform().Rotator(), _Rotator_AnimateAngle, DeltaTime, 1.0f);
			_UpperMeshSpindle->SetRelativeRotation(NewRotation);

			if (NewRotation.Equals(_Rotator_AnimateAngle, 0.1f))
			{
				_FSM_Status = FSM_Toilet_Model1::FSM_Stay;
			}
			break;
		case FSM_Toilet_Model1::FSM_Stay:
			break;		
		}
	}

}

void APuzzleObject_Toilet::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool adnonno, const FHitResult &whatitis)
{
	if (_FSM_Status == FSM_Toilet_Model1::FSM_Sleep && _bMagicActive)
	{
		ADummyCharacter* Temp = Cast<ADummyCharacter>(OtherActor);
		if (Temp != NULL)
		{
			//무언가 여차저차해서 이하생략
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Oh... Toilet is Open..!")));

			_FSM_Status = FSM_Toilet_Model1::FSM_Moving;
		}
	}
	
}

void APuzzleObject_Toilet::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void APuzzleObject_Toilet::Action(float DeltaSeconds)
{



}