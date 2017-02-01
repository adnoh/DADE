// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Puzzle_Trigger.generated.h"
UENUM()
enum class eID_Trigger :uint8
{
	TriggerID_Plumger UMETA(DisplayName = "PlumgerActZone"),
	TriggerID_JumpZone UMETA(DisplayName = "JumpZone"),
	TriggerID_ClimingZone UMETA(DisplayName = "ClimingZone"),
	TriggerID_WaterZone UMETA(DisplayName = "WaterZone"),
	Count_TriggerID UMETA(DisplayName = "Count")
};

UCLASS()
class DADE_API APuzzle_Trigger : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent*_TriggerBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UArrowComponent*_Arrow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent*_Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AActor*> _TargetClass;//트리거에서 해결하거나 부딫힌데서 해결하거나
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int _nTriggerNum;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditParameter)
	eID_Trigger m_TriggerID;
	// Sets default values for this actor's properties
	APuzzle_Trigger();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool adnonno, const FHitResult &whatitis);
	UFUNCTION()
		virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	
	
};
