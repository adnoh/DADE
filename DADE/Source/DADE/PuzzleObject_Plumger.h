// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Puzzle_Object.h"
#include "PuzzleObject_Plumger.generated.h"


UCLASS()
class DADE_API APuzzleObject_Plumger : public APuzzle_Object
{
	GENERATED_BODY()

private:
	enum FSM_Plumger_Model1
	{
		FSM_Sleep = 0,
		FSM_Stay,
		FSM_Follow,
		FSM_TriggerActive,
		Count_FSM
	};
public:
	APuzzleObject_Plumger();
	~APuzzleObject_Plumger();
		virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void Action(float DeltaSeconds);
	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool adnonno, const FHitResult &whatitis);
	UFUNCTION()
		virtual	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	
	//행동 모델 1:마법에 걸리면 주인공을 추적, 적절한 트리거에 걸리면 회전하는 상태로 넘어가고 끝나면 그대로 대기
	FSM_Plumger_Model1 _FSM_Status;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* _StickSpindle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditParameter)
		FRotator _Rotator_AnimateAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditParameter)
		AActor* _AFollowTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector _fvec_Velocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditParameter)
		float _fFollowSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditParameter)
		float _fFollowRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditParameter)
		float _fFriction;
	
	
};
