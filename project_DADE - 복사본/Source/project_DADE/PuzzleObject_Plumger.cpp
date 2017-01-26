// Fill out your copyright notice in the Description page of Project Settings.

#include "project_DADE.h"
#include "PuzzleObject_Plumger.h"
#include "DummyCharacter.h"
#include "Puzzle_Trigger.h"
APuzzleObject_Plumger::APuzzleObject_Plumger()
{
	_FSM_Status = FSM_Plumger_Model1::FSM_Sleep;
	_StickSpindle = CreateDefaultSubobject<UBoxComponent>(TEXT("Spindle"));
	_StickSpindle->SetupAttachment(RootComponent);
}
APuzzleObject_Plumger::~APuzzleObject_Plumger()
{

}

void APuzzleObject_Plumger::BeginPlay()
{
	Super::BeginPlay();
	APuzzle_Object::BeginPlay();


}

// Called every frame
void APuzzleObject_Plumger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector Dir;
	float length;
	FRotator NewRotation;

	if (_bMagicActive) {
		switch (_FSM_Status)
		{
		case FSM_Plumger_Model1::FSM_Sleep:
			break;
		case FSM_Plumger_Model1::FSM_Follow:
			 Dir = _AFollowTarget->GetActorLocation() - GetActorLocation();
			 length;
			Dir.ToDirectionAndLength(Dir, length);//노말라이즈화 된건지 확인해보기
			Dir.Z = 0;
			if (length > _fFollowRange)
				AddActorWorldOffset(Dir*_fFollowSpeed*DeltaTime, true);
			break;
		case FSM_Plumger_Model1::FSM_Stay:
			break;
		case FSM_Plumger_Model1::FSM_TriggerActive:
			NewRotation = FMath::RInterpTo(_StickSpindle->GetRelativeTransform().Rotator(), _Rotator_AnimateAngle, DeltaTime, 1.0f);
			_StickSpindle->SetRelativeRotation(NewRotation);
			if (NewRotation.Equals(_Rotator_AnimateAngle, 0.1f))
			{
				_FSM_Status = FSM_Plumger_Model1::FSM_Stay;
			}
			break;
		}
	}
	
}

void APuzzleObject_Plumger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool adnonno, const FHitResult &whatitis)
{
	if (_FSM_Status == FSM_Plumger_Model1::FSM_Sleep && _bMagicActive)
	{
		ADummyCharacter* Temp = Cast<ADummyCharacter>(OtherActor);
		if (Temp != NULL)
		{
			//무언가 여차저차해서 주인공을 따라가게 된다는 연출?
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("AnyWay... Plumger decides following Hero...")));

			_FSM_Status = FSM_Plumger_Model1::FSM_Follow;
		}
	}
	else if (_FSM_Status == FSM_Plumger_Model1::FSM_Follow && _bMagicActive) {
		APuzzle_Trigger* Temp2 = Cast<APuzzle_Trigger>(OtherActor);
		if (Temp2 != NULL &&Temp2->m_TriggerID == eID_Trigger::TriggerID_Plumger)//트리거 작동
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("And... Plumger rotate for Hero")));
			
			_FSM_Status = FSM_Plumger_Model1::FSM_TriggerActive;

			//방향 조정
			SetActorLocation(Temp2->GetActorLocation());			
			SetActorRotation(Temp2->GetActorRotation());
			
		}
	}
}

void APuzzleObject_Plumger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void APuzzleObject_Plumger::Action(float DeltaSeconds)
{



}
