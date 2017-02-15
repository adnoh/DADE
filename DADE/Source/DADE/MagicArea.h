// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MagicArea.generated.h"

UCLASS()
class DADE_API AMagicArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagicArea();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* _SM_Area;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool _bActive;
	void ChangeAreaActive(bool setBool);
	float _fMagicArea;

	UFUNCTION()
	void OnOverlapBegin_MagicArea(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool adnonno, const FHitResult &whatitis);
	UFUNCTION()
	void OnOverlapEnd_MagicArea(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EditParameter)
		UParticleSystem* m_MagicAreaEffect;
};
