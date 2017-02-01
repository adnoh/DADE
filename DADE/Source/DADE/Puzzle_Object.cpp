// Fill out your copyright notice in the Description page of Project Settings.

#include "DADE.h"
#include "Puzzle_Object.h"


// Sets default values
APuzzle_Object::APuzzle_Object()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_Box_CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	_Box_CollisionBox->SetupAttachment(RootComponent);

	_Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	_Arrow->SetupAttachment(RootComponent);

	_StaticMesh_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_StaticMesh_Mesh->SetupAttachment(RootComponent);

	_Billboard_MagickEffect = CreateDefaultSubobject<UMaterialBillboardComponent>(TEXT("Billboard MagicEffect"));
	_Billboard_MagickEffect->SetupAttachment(RootComponent);
	_Billboard_MagickEffect->SetVisibility(false);
	
	
	_Box_CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APuzzle_Object::OnOverlapBegin);
	_Box_CollisionBox->OnComponentEndOverlap.AddDynamic(this, &APuzzle_Object::OnOverlapEnd);
	_bMagicActive = false;

	
}

// Called when the game starts or when spawned
void APuzzle_Object::BeginPlay()
{
	Super::BeginPlay();

	if (_Billboard_MagickEffect!=NULL&&_Billboard_MagickEffect->IsVisible() == true)
		_Billboard_MagickEffect->SetVisibility(false);
}

// Called every frame
void APuzzle_Object::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void APuzzle_Object::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool adnonno, const FHitResult &whatitis)
{

}

void APuzzle_Object::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void APuzzle_Object::Action(float DeltaSeconds)
{

}
void APuzzle_Object::OnMagickActive()
{
	if (_bMagicActive)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Magic off")));
		_bMagicActive = false;
		_Billboard_MagickEffect->SetVisibility(false);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Magic on")));
		_bMagicActive = true;
		//_Billboard_MagickEffect->Activate(true);
		_Billboard_MagickEffect->SetVisibility(true);
	}
	

}
