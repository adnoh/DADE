// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Puzzle_Object.generated.h"

UCLASS()
class PROJECT_DADE_API APuzzle_Object : public APawn
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UBoxComponent*_Box_CollisionBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UArrowComponent*_Arrow;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent*_StaticMesh_Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool _bMagicActive;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UMaterialBillboardComponent* _Billboard_MagickEffect;

// Sets default values for this actor's properties
	APuzzle_Object();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void Action(float DeltaSeconds);
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool adnonno, const FHitResult &whatitis);
	UFUNCTION()
		virtual	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		virtual void OnMagickActive();//뭐가 더 필요할 거 같은데 터치시 피킹됬을때 누군가 호출할 함수
	
};
