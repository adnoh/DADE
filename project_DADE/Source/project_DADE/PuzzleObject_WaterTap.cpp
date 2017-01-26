// Fill out your copyright notice in the Description page of Project Settings.

#include "project_DADE.h"
#include "PuzzleObject_WaterTap.h"
#include "DummyCharacter.h"

APuzzleObject_WaterTap::APuzzleObject_WaterTap()
{
	_FSM_Status = FSM_WaterTap_Model1::FSM_Sleep;
	_ColWaveZone = CreateDefaultSubobject<UBoxComponent>(TEXT("Spindle"));
	_ColWaveZone->SetupAttachment(RootComponent);
}
APuzzleObject_WaterTap::~APuzzleObject_WaterTap()
{

}

void APuzzleObject_WaterTap::BeginPlay()
{
	Super::BeginPlay();
	APuzzle_Object::BeginPlay();


}

// Called every frame
void APuzzleObject_WaterTap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> CollectedActors;
	switch (_FSM_Status)
	{

	case	FSM_WaterTap_Model1::FSM_Sleep:
		
		_ColWaveZone->GetOverlappingActors(CollectedActors);

		for (int32 iCollected = 0; iCollected < CollectedActors.Num(); ++iCollected)
		{
			ADummyCharacter*Temp = Cast<ADummyCharacter>(CollectedActors[iCollected]);
			if (Temp != NULL)
			{
				Temp->AddActorWorldOffset(_Arrow->GetForwardVector() * _fPushPower*DeltaTime);

			}
		}
		break;
	case	FSM_WaterTap_Model1::FSM_TurnOff:
		break;
	}

	

}

void APuzzleObject_WaterTap::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool adnonno, const FHitResult &whatitis)
{
	if (_FSM_Status == FSM_WaterTap_Model1::FSM_Sleep && _bMagicActive)
	{
		ADummyCharacter* Temp = Cast<ADummyCharacter>(OtherActor);
		if (Temp != NULL)
		{			
			_FSM_Status = FSM_WaterTap_Model1::FSM_TurnOff;
		}
	}
	
}

void APuzzleObject_WaterTap::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void APuzzleObject_WaterTap::Action(float DeltaSeconds)
{



}


