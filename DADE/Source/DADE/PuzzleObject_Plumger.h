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
	
	
	//�ൿ �� 1:������ �ɸ��� ���ΰ��� ����, ������ Ʈ���ſ� �ɸ��� ȸ���ϴ� ���·� �Ѿ�� ������ �״�� ���
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
