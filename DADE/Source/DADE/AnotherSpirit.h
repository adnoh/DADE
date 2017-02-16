// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "DummyCharacter.h"
#include "GameFramework/Actor.h"
#include "AnotherSpirit.generated.h"

UCLASS()
class DADE_API AAnotherSpirit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAnotherSpirit();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UBoxComponent*_Box_CollisionBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UArrowComponent*_Arrow;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent*_StaticMesh_Mesh;
	
	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool adnonno, const FHitResult &whatitis);
	UFUNCTION()
		virtual	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditParameter)
		ADummyCharacter* _HeroActor;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	bool _fResscued;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EditParameter)
		UParticleSystem* m_MagicAreaEffect;
};
