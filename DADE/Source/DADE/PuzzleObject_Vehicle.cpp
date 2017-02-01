// Fill out your copyright notice in the Description page of Project Settings.

#include "DADE.h"
#include "PuzzleObject_Vehicle.h"
#include "DummyCharacter.h"
#include "Puzzle_Trigger.h"


APuzzleObject_Vehicle::APuzzleObject_Vehicle()
{
	_ARidingTarget = NULL;

	_Box_RidingPos = CreateDefaultSubobject<UBoxComponent>(TEXT("RidingPos"));
	_Box_RidingPos->SetupAttachment(RootComponent);

	_Box_EscapePos = CreateDefaultSubobject<UBoxComponent>(TEXT("EscapePos"));
	_Box_EscapePos->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = true;
	Controller = NULL;
}

APuzzleObject_Vehicle::~APuzzleObject_Vehicle()
{

}

void APuzzleObject_Vehicle::BeginPlay()
{
	Super::BeginPlay();
	APuzzle_Object::BeginPlay();


}
void APuzzleObject_Vehicle::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	
	InputComponent->BindAxis("Move_Foward", this, &APuzzleObject_Vehicle::MoveForward);
	InputComponent->BindAxis("Move_Right", this, &APuzzleObject_Vehicle::MoveRight);
	InputComponent->BindAction("ActionActive", IE_Pressed, this, &APuzzleObject_Vehicle::MoveAction);
}
// Called every frame
void APuzzleObject_Vehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (_ARidingTarget != NULL) {
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("oh ye")));
		//_ARidingTarget->SetActorEnableCollision(false);
		_ARidingTarget->SetActorLocation(_Box_RidingPos->GetComponentLocation());//RidingPos->GetComponentLocation());
		_ARidingTarget->SetActorRotation(GetActorRotation());
		
		//AddActorWorldOffset(_fvec_Velocity, true);
		//_fvec_Velocity

	}
	
	m_FloatingAngle += DeltaTime;
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("error %f"), sinf(m_FloatingAngle)));

	AddActorWorldOffset(FVector(0, 0, m_fFloatingHeighth*sinf(m_FloatingAngle)));
	if (m_FloatingAngle > 2 * PI)
		m_FloatingAngle = 0;
	
}

void APuzzleObject_Vehicle::MoveAction()
{
	
	ADummyCharacter* Temp = Cast<ADummyCharacter>(_ARidingTarget);
	APlayerController *tempController;
	if (Temp != NULL &&Temp->m_FSM_Status == ADummyCharacter::eFSM_Hero::FSM_Riding)
	{

		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("oh ye")));

		Temp->m_FSM_Status = ADummyCharacter::eFSM_Hero::FSM_Normal;

		tempController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		Temp->SetActorLocation(_Box_EscapePos->GetComponentLocation());
		Temp->Changer = NULL;
		
		_ARidingTarget = NULL;
		tempController->Possess(Temp);
		Temp->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
		tempController = NULL;
		Temp = NULL;
	}
	else {
		if(Temp != NULL)
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("error %d"), (int)Temp->m_FSM_Status));
	}
}
void APuzzleObject_Vehicle::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool adnonno, const FHitResult &whatitis)
{
	if (_bMagicActive)
	{
		ADummyCharacter* Temp = Cast<ADummyCharacter>(OtherActor);
		if (Temp != NULL &&Temp->m_FSM_Status != ADummyCharacter::eFSM_Hero::FSM_Riding)
		{
	
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("DuckDuck")));

			Temp->m_FSM_Status = ADummyCharacter::eFSM_Hero::FSM_EnableRiding;
			Temp->Changer = this;
		}
	}
}

void APuzzleObject_Vehicle::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (_bMagicActive)
	{
		ADummyCharacter* Temp = Cast<ADummyCharacter>(OtherActor);
		if (Temp != NULL)
		{

			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("An-DuckDuck")));

			Temp->m_FSM_Status = ADummyCharacter::eFSM_Hero::FSM_Normal;
			Temp->Changer = NULL;
			
		}
	}
}

void APuzzleObject_Vehicle::Action(float DeltaSeconds)
{



}
void APuzzleObject_Vehicle::MoveForward(float Value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("riding!!!!! %f %f %f"), Value, Value, Value));

	if ((Controller != NULL) && (Value != 0.0f))
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("An-ApAp")));
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddActorWorldOffset(Direction*Value);
		//AddMovementInput(Direction, Value);
		
	}
}

void APuzzleObject_Vehicle::MoveRight(float Value)
{
	
	if ((Controller != NULL) && (Value != 0.0f))
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("An-yopyop")));
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddActorWorldOffset(Direction*Value);
	}
}