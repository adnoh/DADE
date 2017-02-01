// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Puzzle_Object.h"
#include "PuzzleObject_WaterTap.generated.h"

/**
 * 
 */
UCLASS()
class DADE_API APuzzleObject_WaterTap : public APuzzle_Object
{
	GENERATED_BODY()
		enum FSM_WaterTap_Model1
	{
		FSM_Sleep = 0,
		FSM_TurnOff,	
		Count_FSM
	};
public:
	APuzzleObject_WaterTap();
	~APuzzleObject_WaterTap();
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void Action(float DeltaSeconds);
	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool adnonno, const FHitResult &whatitis);
	UFUNCTION()
		virtual	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	
	FSM_WaterTap_Model1 _FSM_Status;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* _ColWaveZone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditParameter)
		float _fPushPower;

	
	
	
};
