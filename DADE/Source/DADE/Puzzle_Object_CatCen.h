// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Puzzle_Object.h"
#include "Puzzle_Object_CatCen.generated.h"

/**
 * 
 */
UCLASS()
class DADE_API APuzzle_Object_CatCen : public APuzzle_Object
{
	GENERATED_BODY()
		enum FSM_CatCen_Model1
	{
		FSM_Sleep = 0,
		FSM_Carry,
		FSM_Open,
		Count_FSM
	};
public:
	APuzzle_Object_CatCen();
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UBoxComponent*_RidingPos;
	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool adnonno, const FHitResult &whatitis);
	UFUNCTION()
		virtual	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditParameter)
		AActor* _HeroActor;

	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	FSM_CatCen_Model1 _FSM_State;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool _SmellOpen;
	
};
