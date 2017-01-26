// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Puzzle_Object.h"
#include "PuzzleObject_Vehicle.generated.h"

/**
 *
 */
UCLASS()
class PROJECT_DADE_API APuzzleObject_Vehicle : public APuzzle_Object
{
	GENERATED_BODY()
public:
	APuzzleObject_Vehicle();
	~APuzzleObject_Vehicle();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditParameter)
		float m_fFloatingHeighth;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditParameter)
		APawn* _ARidingTarget;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UBoxComponent* _Box_RidingPos;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UBoxComponent* _Box_EscapePos;
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	void Action(float DeltaSeconds);
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool adnonno, const FHitResult &whatitis);
	UFUNCTION()	
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		 void MoveAction( );
	UFUNCTION()
		virtual void MoveForward(float Value);
	UFUNCTION()
		virtual void MoveRight(float Value);

	float m_FloatingAngle;

};
