// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Puzzle_Object.h"
#include "PuzzleObject_Toilet.generated.h"

/**
 * 
 */
UCLASS()
class DADE_API APuzzleObject_Toilet : public APuzzle_Object
{
	GENERATED_BODY()
		enum FSM_Toilet_Model1// 이것도 언뜻 통합해야할지도 모르겠다.
	{
		FSM_Sleep = 0,
		FSM_Stay,
		FSM_Moving,
		Count_FSM
	};

public:
	APuzzleObject_Toilet();
	~APuzzleObject_Toilet();
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void Action(float DeltaSeconds);
	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool adnonno, const FHitResult &whatitis);
	UFUNCTION()
		virtual	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		UBoxComponent *_UpperMeshSpindle;
	

	//행동 모델 1:마법에 걸리고 주인공과 접촉하면 뚜껑열리기 시작,회전이 끝나면 대기
	FSM_Toilet_Model1 _FSM_Status;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditParameter)
		FRotator _Rotator_AnimateAngle;

	
	
};
