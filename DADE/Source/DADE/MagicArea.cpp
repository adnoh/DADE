// Fill out your copyright notice in the Description page of Project Settings.

#include "DADE.h"
#include "MagicArea.h"
#include "Puzzle_Object.h"

// Sets default values


AMagicArea::AMagicArea()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_SM_Area = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MagicArea"));
	_SM_Area->SetupAttachment(RootComponent);
	_SM_Area->SetVisibility(false);
	_SM_Area->OnComponentBeginOverlap.AddDynamic(this, &AMagicArea::OnOverlapBegin_MagicArea);
	_SM_Area->OnComponentEndOverlap.AddDynamic(this, &AMagicArea::OnOverlapEnd_MagicArea);
	_bActive = false;
	_fMagicArea = 0;
}

// Called when the game starts or when spawned
void AMagicArea::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMagicArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float tmp_AreaScale;
	if (_bActive) {
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("ada on")));
		tmp_AreaScale = FMath::FInterpTo(_SM_Area->GetComponentTransform().GetScale3D().X, _fMagicArea, DeltaTime, 0.4f);
		if (tmp_AreaScale <= _fMagicArea - 0.1f || tmp_AreaScale >= _fMagicArea + 0.1f) {
			//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Grow in %f %f %f"),_SM_Area->GetComponentTransform().GetScale3D().X, tmp_AreaScale, _MagicArea));
			//_SM_Area->GetComponentTransform().SetScale3D(FVector(tmp_AreaScale, tmp_AreaScale, tmp_AreaScale));
			_SM_Area->SetWorldScale3D(FVector(tmp_AreaScale, tmp_AreaScale, tmp_AreaScale));
		}
	}

	

}
void AMagicArea::ChangeAreaActive(bool setBool)
{
	if (setBool)
	{

		
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("magic on")));
		_bActive = true;
		_SM_Area->SetVisibility(true);

	}
	else {

		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("magic offff")));
		_bActive = false;
		_SM_Area->SetWorldScale3D(FVector(1, 1, 1));
		_SM_Area->SetVisibility(false);
	}
}
void AMagicArea::OnOverlapBegin_MagicArea(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool adnonno, const FHitResult &whatitis)
{
	APuzzle_Object*Temp = Cast<APuzzle_Object>(OtherActor);
	if (Temp != NULL)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Area overlap")));
		//Temp->OnMagickActive();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_MagicAreaEffect, Temp->GetActorTransform(), true);
		Temp->_bInside_MagicArea = true;
	}

}
void AMagicArea::OnOverlapEnd_MagicArea(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APuzzle_Object*Temp = Cast<APuzzle_Object>(OtherActor);
	if (Temp != NULL)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Area overlap")));
		//Temp->OnMagickActive();
		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_MagicAreaEffect, Temp->GetActorTransform(), true);
		Temp->_bInside_MagicArea = false;
	}
}
