// Fill out your copyright notice in the Description page of Project Settings.

#include "DADE.h"
#include "DADE_Playable.h"


// Sets default values
ADADE_Playable::ADADE_Playable()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADADE_Playable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADADE_Playable::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ADADE_Playable::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

